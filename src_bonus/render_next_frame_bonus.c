/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/01 19:06:09 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	intersect_plane(t_obj *plane, t_ray *ray)
{
	double		denominator;
	double		distance;

	denominator = vector3_scalar(plane->orientation, ray->orientation);
	if (denominator > EPSILON)
	{
		distance = vector3_scalar(matrix3_subtract(plane->position, ray->position), plane->orientation) / denominator;
		if (distance < EPSILON || (ray->distance < distance && ray->distance))
			return ;
		ray->normal = vector3_negate(plane->orientation);
	}
	else if (denominator < -EPSILON)
	{
		denominator = vector3_scalar(vector3_negate(plane->orientation), ray->orientation);
		distance = vector3_scalar(matrix3_subtract(plane->position, ray->position), vector3_negate(plane->orientation)) / denominator;
		if (distance < EPSILON || (ray->distance < distance && ray->distance))
			return ;
		ray->normal = plane->orientation;
	}
	else
		return ;
	ray->color = plane->colour;
	ray->distance = distance;
	ray->coordinates = matrix3_addition(ray->position, vector3_multiply(ray->orientation, distance));
}

static void	intersect_sphere(t_obj *sphere, t_ray *ray)
{
	t_vector3	d;
	t_vector3	p;
	t_quad		q;
	t_ray		new_ray;

	kd_memset(&q, 0, sizeof(t_quad));
	new_ray = *ray;
	d = vector3_multiply(ray->orientation, 1);//sphere->max_distance);
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
	ray->color = sphere->colour;
}

static void	intersect(t_ray *ray, t_mlx *mlx)
{
	t_obj		*obj;

	obj = mlx->obj;
	while (obj)
	{
		if (obj->type == PLANE)
			intersect_plane(obj, ray);
		else if (obj->type == SPHERE)
		{
			obj->max_distance = 1;
			intersect_sphere(obj, ray);
		}
		obj = obj->next;
	}
}

static t_bool compute_shadow(t_light *light, t_ray *ray, t_mlx *mlx)
{
	t_ray	new_ray;

	kd_memset(&new_ray, 0, sizeof(t_ray));
	new_ray.position = ray->coordinates;
	new_ray.orientation = vector3_normalise(matrix3_subtract(light->position, ray->coordinates));
	intersect(&new_ray, mlx);
	if (new_ray.distance && new_ray.distance < vector3_distance(light->position, ray->coordinates))
		return (TRUE);
	return (FALSE);
}

static unsigned int	compute_light(t_ray *ray, t_mlx *mlx)
{
	t_light		*light;
	t_vector3	l;
	double		fctr;
	t_color		colour;

	if (!ray->distance)
		return (0x000000);
	colour = colour_matrix_amplify(ray->color, colour_amplify(mlx->ambient->color, mlx->ambient->bright));
	light = mlx->light;
	while (light)
	{
		l = vector3_normalise(matrix3_subtract(light->position, ray->coordinates));
		fctr = vector3_scalar(ray->normal, l);
		if (fctr < 0 || compute_shadow(light, ray, mlx))
			fctr = 0;
		colour = colour_add(colour, colour_amplify(colour_matrix_amplify(ray->color, colour_amplify(light->color, light->bright)), fctr));
		light = light->next;
	}
	return (colour_rgb2hex(colour));
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
//	printf("c %f\n", ray->position.x);
	ray->orientation = vector3_rotate(camera->orient, camera->rotate);
}

static void	raytrace(t_xy pixel, t_ray *ray, t_mlx *mlx)
{
	t_vector2	step;
//	t_obj		*obj;

	step = new_vector2((pixel.x - mlx->width / (double)2) / mlx->width * (double)2, -(pixel.y - mlx->height / (double)2) / mlx->width * (double)2);
	if (mlx->view == 0)
		ray_perspective_tan(mlx->camera, step, ray);
	else if (mlx->view == 1)
		ray_perspective_spherise(mlx->camera, step, ray);
	else if (mlx->view == 2)
		ray_orthographic(mlx->camera, step, ray);
	intersect(ray, mlx);
}

static void	animate(t_mlx *mlx)
{
	t_vector2	q;

	q = mlx->camera->rotate;
	if (mlx->play)
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
			mlx->play = FALSE;
		kd_free(mlx->hud);
		mlx->hud = kd_strf("x %d y %d", (int)q.u, (int)q.v);
	}
	mlx->camera->rotate.u = q.u;
	mlx->camera->rotate.v = q.v;
}

void	*thread_loop(void *thread_void)
{
	t_mlx *mlx;
	t_thread *thread;
	t_xy	pixel;
	t_ray	ray;

	thread = thread_void;
	mlx = mlx_void;
	while (!mlx->play)
	{
		pixel.y = 0;
		while (pixel.y + < mlx->height)
		{
			i
			pixel.x = 0;
			while (pixel.x < mlx->width)
			{
				kd_memset(&ray, 0, sizeof(t_ray));
				raytrace(pixel, &ray, mlx);
				my_mlx_pixel_put(mlx->sim, pixel.x, pixel.y,
								 compute_light(&ray, mlx));
				pixel.x++;
			}
			pixel.y++;
		}
	}
	return (NULL);
}

int	render_next_frame(t_mlx *mlx)
{
	animate(mlx);
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->sim->ptr, 0, 0);
	hud(mlx);
	return (0);
}

//int	render_next_frame(t_mlx *mlx)
//{
//	t_xy	pixel;
//	t_ray	ray;
//
//	animate(mlx);
////	kd_free(mlx->hud);
////	mlx->hud = kd_strf("x %d y %d", mlx->camera->rotate.x, mlx->camera->rotate.y);
//	pixel.y = 0;
//	while (pixel.y < mlx->win_h)
//	{
//		pixel.x = 0;
//		while (pixel.x < mlx->win_w)
//		{
//			kd_memset(&ray, 0, sizeof(t_ray));
//			raytrace(pixel, &ray, mlx);
//			my_mlx_pixel_put(mlx->sim, pixel.x, pixel.y, compute_light(&ray, mlx));
//			pixel.x++;
//		}
//		pixel.y++;
//	}
//	mlx_put_image_to_window(mlx->init, mlx->win, mlx->sim->ptr, 0, 0);
//	hud(mlx);
//	return (0);
//}
