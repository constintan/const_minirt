/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/02 22:49:07 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	math_discriminant(double a, double b, double c)
{
	return (pow(b, 2) - 4 * a * c);
}

static void	intersect_plane(t_plane *plane, t_ray *ray)
{
	double		denominator;
	double		distance;

	denominator = vector3_scalar(plane->orient, ray->orientation);
	if (denominator > EPSILON)
	{
		//t =
		distance = vector3_scalar(matrix3_subtract(plane->position, ray->position), plane->orient) / denominator;
		if (distance < EPSILON || (ray->distance < distance && ray->distance))
			return ;
		ray->normal = vector3_negate(plane->orient);
	}
	else if (denominator < -EPSILON)
	{
		denominator = vector3_scalar(vector3_negate(plane->orient), ray->orientation);
		distance = vector3_scalar(matrix3_subtract(plane->position, ray->position), vector3_negate(plane->orient)) / denominator;
		if (distance < EPSILON || (ray->distance < distance && ray->distance))
			return ;
		ray->normal = plane->orient;
	}
	else
		return ;
	ray->color = plane->color;
	ray->distance = distance;
	ray->coordinates = matrix3_addition(ray->position, vector3_multiply(ray->orientation, distance));
}

static void	intersect_sphere(t_sphere *sphere, t_ray *ray)
{
	t_vector3	d;
	t_vector3	p;
	t_quad		q;
	t_ray		new_ray;

	kd_memset(&q, 0, sizeof(t_quad));
	new_ray = *ray;
	//x0-cx ; y0-cy ; z0-cz
	d = ray->orientation; //vector3_multiply(ray->orientation, 1); //max_distance
	p = matrix3_subtract(ray->position, sphere->position);
	q.a = vector3_sumpow2(d);
	q.b = 2 * d.x * p.x + 2 * d.y * p.y + 2 * d.z * p.z;
	q.c = vector3_sumpow2(sphere->position) + vector3_sumpow2(ray->position) - 2 * vector3_scalar(sphere->position, ray->position) - pow(sphere->radius, 2);
	q.d = math_discriminant(q.a, q.b, q.c);
	if (q.d < 0)
		return ;
	new_ray.t = (-q.b - sqrt(q.d)) / (2 * q.a);
	if (new_ray.t < EPSILON)
		new_ray.t = (-q.b + sqrt(q.d)) / (2 * q.a);
	new_ray.coordinates = matrix3_addition(ray->position, vector3_multiply(d, new_ray.t));
	new_ray.distance = vector3_distance(ray->position, new_ray.coordinates);
	if (new_ray.t < EPSILON || (ray->distance < new_ray.distance && ray->distance))
		return ;
	*ray = new_ray;
	ray->normal = vector3_normalise(matrix3_subtract(ray->coordinates, sphere->position));
	ray->color = sphere->color;
}

static void	intersect(t_ray *ray, t_scene *scene)
{
	t_plane		*plane;
	t_sphere	*sphere;

	plane = scene->planes;
	while (plane)
	{
		intersect_plane(plane, ray);
		plane = plane->next;
	}
	sphere = scene->spheres;
	while (sphere)
	{
		intersect_sphere(sphere, ray);
		sphere = sphere->next;
	}
}

static t_bool compute_shadow(t_light *light, t_vector3 l, t_ray *ray, t_scene *scene)
{
	t_ray	new_ray;

	kd_memset(&new_ray, 0, sizeof(t_ray));
	new_ray.position = ray->coordinates;
	new_ray.orientation = vector3_normalise(matrix3_subtract(light->position, ray->coordinates));
	intersect(&new_ray, scene);
	if (new_ray.distance && new_ray.distance < vector3_distance(light->position, ray->coordinates))
		return (TRUE);
	return (FALSE);
}

static t_color	compute_light(t_ray *ray, t_scene *scene)
{
	t_light		*light;
	t_vector3	l;
	double		fctr;
	t_color		color;

//	new_ray = compute_mirror_angle(ray);
//	intersect(new_ray, scene);
//	new_ray == ray из камеры
//	new_ray.color == цвет объекта в отражении шара

//	если пересечений не было, то distance по дефолту = 0
	if (!ray->distance)
		return (new_color(DEFAULT_BG_COLOR));
	color = colour_matrix_amplify(ray->color, colour_amplify(scene->ambient->color, scene->ambient->bright));
	light = scene->light;
	while (light && !scene->no_lights)
	{
		l = vector3_normalise(matrix3_subtract(light->position, ray->coordinates));
		fctr = vector3_scalar(ray->normal, l);
		if (fctr < 0 || (!scene->no_shadows && compute_shadow(light, ray, scene)))
			fctr = 0;
		color = colour_add(color, colour_amplify(colour_matrix_amplify(ray->color, colour_amplify(light->color, light->bright)), fctr));
		light = light->next;
		if (scene->one_light)
			light = NULL;
	}
	return (color);
}

static void	ray_perspective_spherise(t_camera *camera, t_vector2 step, t_ray *ray)
{
	ray->position = camera->position;
	step.u = camera->fov / 2 * step.u;
	step.v = camera->fov / 2 * step.v;
	ray->orientation = vector3_rotate(new_vector3(0, 0, 1), step);
	ray->orientation = vector3_rotate(ray->orientation, camera->rotate);
}

static void ray_perspective_tan(t_camera *camera, t_vector2 step, t_ray *ray)
{
	ray->position = camera->position;
	ray->orientation = new_vector3(tan(camera->fov / 2 * (M_PI / 180))
			* step.u, tan(camera->fov / 2 * (M_PI / 180)) * step.v, 1);
	ray->orientation = vector3_normalise(ray->orientation);
	ray->orientation = vector3_rotate(ray->orientation, camera->rotate);
}

static void ray_orthographic(t_camera *camera, t_vector2 step, t_ray *ray)
{
	ray->position.x = camera->position.x + step.u * camera->zoom;
	ray->position.y = camera->position.y + step.v * camera->zoom;
	ray->position.z = camera->position.z;
	ray->position = matrix3_addition(vector3_rotate(matrix3_subtract(ray->position, camera->position), camera->rotate), camera->position);
	ray->orientation = vector3_rotate(new_vector3(0, 0, 1), camera->rotate);
}

static void	raytrace(t_xy pixel, t_ray *ray, t_scene *scene)
{
	t_vector2	step;

	step = new_vector2((pixel.x - scene->width / (double)2) / scene->width * (double)2, -(pixel.y - scene->height / (double)2) / scene->width * (double)2);
	if (scene->view == 0)
		ray_perspective_tan(scene->camera, step, ray);
	else if (scene->view == 1)
		ray_perspective_spherise(scene->camera, step, ray);
	else if (scene->view == 2)
		ray_orthographic(scene->camera, step, ray);
	intersect(ray, scene);
}

static void	animate(t_scene *scene)
{
	t_vector2	q;

	q = scene->camera->rotate;
	if (scene->play)
	{
		if (q.v >= 360 && q.u < 720 && q.v < 720)
		{
			q.u += 10;
			q.v += 10;
		} else if (q.u == 360)
			q.v += 10;
		else if (q.u < 720 && q.v < 720)
			q.u += 10;
		else
			scene->play = FALSE;
	}
	scene->camera->rotate.u = q.u;
	scene->camera->rotate.v = q.v;
}
#include <sys/time.h>
long	mtv(void)
{
	struct timeval	tv;
	static long		start;

	gettimeofday(&tv, NULL);
	if (!start)
	{
		start = (long) tv.tv_sec * 1000 + tv.tv_usec / 1000;
		return (0);
	}
	return (((long)tv.tv_sec * 1000 + tv.tv_usec / 1000) - start);
}

int	render_next_frame(t_scene *scene)
{
	t_xy	pixel;
	t_ray	ray;
	long	time1;
	static long	time2;

	animate(scene);
	kd_free(scene->hud);
//	scene->hud = kd_strf("x %d y %d", (int)scene->camera->rotate.u, (int)scene->camera->rotate.v);
	time1 = mtv();
	scene->hud = kd_strf("%d", (int)time1 - (int)time2);
	time2 = time1;
	pixel.y = 0;
	while (pixel.y < scene->height)
	{
		pixel.x = 0;
		while (pixel.x < scene->width)
		{
			kd_memset(&ray, 0, sizeof(t_ray));
			raytrace(pixel, &ray, scene);
			draw_pixel(scene->img, pixel.x, pixel.y, compute_light(&ray, scene));
			pixel.x++;
		}
		pixel.y++;
	}
	mlx_put_image_to_window(scene->mlx, scene->window, scene->img->img, 0, 0);
	hud(scene);
	return (0);
}
