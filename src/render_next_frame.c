/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/06 12:57:29 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	math_discriminant(double a, double b, double c)
{
	return (pow(b, 2) - 4 * a * c);
}

//https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
static void	intersect_plane(t_plane *plane, t_ray *ray)
{
	double		denominator;
	double		distance;

	//l⋅n
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
	//l0+l∗t=p
	ray->coordinates = matrix3_addition(ray->position, vector3_multiply(ray->orientation, distance));
}

static void	intersect_cone(t_cone *cone, t_ray *ray)
{
	t_ray	new_ray;
	t_plane	cap;

//	cap.position = matrix3_subtract(vector3_multiply(cone->orient, cone->height), cone->position); //-40
	cap.position = matrix3_addition(cone->position, vector3_multiply(cone->orient, cone->height)); //40
//	cap.position = vector3_multiply(cone->orient, cone->height); //-20
//	printf("c %f %f\n", cap.position.y, cone->position.y);
	cap.orient = cone->orient;
	cap.color = cone->color;
	new_ray = *ray;
	intersect_plane(&cap, &new_ray);
	if (new_ray.distance)
	{
		if (vector3_sumpow2(matrix3_subtract(new_ray.coordinates, cap.position)) <= pow(cone->radius, 2))
		{
			if (vector3_scalar(new_ray.orientation, cap.orient) < 0)
			{
				*ray = new_ray;
				return ;
			}
		}
	}
	t_vector3	d;
	t_vector3	p;
	t_quad		q;
	double		theta;

	theta = atan(cone->radius / cone->height);
	new_ray = *ray;
	d = ray->orientation; //vector3_multiply(ray->orientation, 1); //max_distance
	p = matrix3_subtract(ray->position, cone->position);
	q.a = pow(vector3_scalar(new_ray.orientation, cone->orient), 2) - pow(cos(theta), 2);
	q.b = 2 * (vector3_scalar(new_ray.orientation, cone->orient) *
			vector3_scalar(matrix3_subtract(new_ray.position, cone->position), cone->orient) -
								   vector3_scalar(new_ray.orientation,
												  matrix3_subtract(new_ray.position, cone->position)) * pow(cos(theta), 2));
	q.c = pow(vector3_scalar(matrix3_subtract(new_ray.position, cone->position), cone->orient), 2) -
			vector3_scalar(matrix3_subtract(new_ray.position, cone->position), matrix3_subtract(new_ray.position, cone->position)) * pow(cos(theta), 2);
	q.d = math_discriminant(q.a, q.b, q.c);
	if (q.d < 0)
		return ;
	new_ray.t = (-q.b + sqrt(q.d)) / (2 * q.a);
	if (new_ray.t < EPSILON)
		new_ray.t = (-q.b - sqrt(q.d)) / (2 * q.a);
	new_ray.coordinates = matrix3_addition(ray->position, vector3_multiply(d, new_ray.t));
	if (!(theta < M_PI / 2 && vector3_scalar(matrix3_subtract(new_ray.coordinates, cone->position), cone->orient) > 0))
		return ; // отрезает конус-двойник, но страдает отрисовка изнутри
	if (vector3_distance(new_ray.coordinates, cone->position) > cone->height / cos(theta))
		return ;
	new_ray.distance = vector3_distance(ray->position, new_ray.coordinates);
	if (new_ray.distance < EPSILON || (ray->distance < new_ray.distance && ray->distance))
		return ;
	*ray = new_ray;
	ray->normal = vector3_normalise(matrix3_subtract(new_ray.coordinates, vector3_multiply(cone->orient, vector3_distance(new_ray.coordinates, cone->position) / cos(theta))));
	ray->color = cone->color;
}

//https://www.ccs.neu.edu/home/fell/CS4300/Lectures/Ray-TracingFormulas.pdf
static void	intersect_sphere(t_sphere *sphere, t_ray *ray)
{
	t_vector3	d;
	t_vector3	p;
	t_quad		q;
	t_ray		new_ray;

	new_ray = *ray;
	//x0-cx ; y0-cy ; z0-cz
	d = ray->orientation; //vector3_multiply(ray->orientation, 1); //max_distance
	p = matrix3_subtract(ray->position, sphere->position);
	//сумма квадратов координат
	q.a = vector3_sumpow2(d);
	q.b = 2 * d.x * p.x + 2 * d.y * p.y + 2 * d.z * p.z;
	q.c = vector3_sumpow2(sphere->position) + vector3_sumpow2(ray->position) - 2 * vector3_scalar(sphere->position, ray->position) - pow(sphere->radius, 2);
	q.d = math_discriminant(q.a, q.b, q.c);
	if (q.d < 0)
		return ;
	new_ray.t = (-q.b - sqrt(q.d)) / (2 * q.a);
	new_ray.coordinates = matrix3_addition(ray->position, vector3_multiply(d, new_ray.t));
	new_ray.normal = vector3_normalise(matrix3_subtract(new_ray.coordinates, sphere->position));
	if (new_ray.t < EPSILON)
	{
		new_ray.t = (-q.b + sqrt(q.d)) / (2 * q.a);
		new_ray.coordinates = matrix3_addition(ray->position, vector3_multiply(d, new_ray.t));
		new_ray.normal = vector3_normalise(matrix3_subtract(sphere->position, new_ray.coordinates));
	}
	new_ray.distance = vector3_distance(ray->position, new_ray.coordinates);
	if (new_ray.t < EPSILON || (ray->distance < new_ray.distance && ray->distance))
		return ;
	*ray = new_ray;
	ray->color = sphere->color;
}

static void	intersect(t_ray *ray, t_scene *scene)
{
	t_plane		*plane;
	t_sphere	*sphere;
	t_cone		*cone;

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
	cone = scene->cones;
	while (cone)
	{
		intersect_cone(cone, ray);
		cone = cone->next;
	}
}

static t_bool compute_shadow(t_light *light, t_vector3 l, t_ray *ray, t_scene *scene)
{
	t_ray	new_ray;

	kd_memset(&new_ray, 0, sizeof(t_ray));
	new_ray.position = ray->coordinates;
//	l = vector3_normalise(matrix3_subtract(light->position, ray->coordinates));
	new_ray.orientation = l;
	intersect(&new_ray, scene);
	if (new_ray.distance && new_ray.distance + EPSILON < vector3_distance(light->position, ray->coordinates))
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
		//перпендикулярный нормаль к свету = 0, параллельный = 1
		if (fctr < 0 || (!scene->no_shadows && compute_shadow(light, l, ray, scene)))
			fctr = 0;
		color = colour_add(color, colour_amplify(colour_matrix_amplify(ray->color, colour_amplify(light->color, light->bright)), fctr));
		light = light->next;
		if (scene->one_light)
			light = NULL;
	}
	return (color);
}

//вид без перспективы (ортографический)
static void ray_orthographic(t_camera *camera, t_vector2 step, t_ray *ray)
{
	ray->position.x = camera->position.x + step.u * camera->zoom;
	ray->position.y = camera->position.y + step.v * camera->zoom;
	ray->position.z = camera->position.z;
	ray->position = matrix3_addition(
			vector3_rotate_yx(matrix3_subtract(ray->position, camera->position),
							  camera->rotate), camera->position);
	ray->orientation = vector3_rotate_yx(new_vector3(0, 0, 1), camera->rotate);
}

//пересчет fov в координаты сцены через тангенс
static void ray_perspective_tan(t_camera *camera, t_vector2 step, t_ray *ray)
{
	ray->position = camera->position;
	ray->orientation = new_vector3(tan(camera->fov / 2 * (M_PI / 180))
			* step.u, tan(camera->fov / 2 * (M_PI / 180)) * step.v, 1);
	ray->orientation = vector3_normalise(ray->orientation);
	ray->orientation = vector3_rotate_yx(ray->orientation, camera->rotate);
}

//пересчет fov в координаты сцены через сферу
static void	ray_perspective_spherise(t_camera *camera, t_vector2 step, t_ray *ray)
{
	ray->position = camera->position;
	step.v = camera->fov / 2 * step.v;
	step.u = camera->fov / 2 * step.u;
	ray->orientation = vector3_rotate_yx(new_vector3(0, 0, 1), step);
	ray->orientation = vector3_rotate_yx(ray->orientation, camera->rotate);
}

//пересчет fov в координаты сцены через с глобальной поправкой искажения
static void	ray_perspective_spherise2(t_camera *camera, t_vector2 step, t_ray *ray)
{
	ray->position = camera->position;
	step.v = camera->fov / 2 * step.v * (0.5 + 0.5 * cos(M_PI / 2 * fabs(step.u)));
	step.u = camera->fov / 2 * step.u;
	ray->orientation = vector3_rotate_yx(new_vector3(0, 0, 1), step);
	ray->orientation = vector3_rotate_yx(ray->orientation, camera->rotate);
}

//пересчет fov в координаты сцены через складывание векторов по 2 осям
static void	ray_perspective_spherise3(t_camera *camera, t_vector2 step, t_ray *ray)
{
	t_vector3	tempy;
	t_vector3	tempx;

	ray->position = camera->position;
	step.v = camera->fov / 2 * step.v;
	step.u = camera->fov / 2 * step.u;
	tempy = vector3_rotate_yx(new_vector3(0, 0, 1), step);
	tempx = vector3_rotate_xy(new_vector3(0, 0, 1), step);
	ray->orientation = vector3_rotate_yx(vector3_normalise(matrix3_addition(tempx, tempy)), camera->rotate);
}

//пересчет fov в координаты сцены через кватернионы, где fov == обзору по диагонали
static void	ray_perspective_quaternion(t_scene *scene, t_xy pixel, t_ray *ray)
{
	double		theta;
	t_vector3	axis;
	double		radius;
	t_vector2	step;

	ray->position = scene->camera->position;
	radius = sqrt(pow(scene->width / (double)2, 2) + pow(scene->height / (double)2, 2));
	step.u = (pixel.x - scene->width / (double)2) / radius;
	step.v = (pixel.y - scene->height / (double)2) / radius;
	theta = sqrt(pow(step.u, 2) + pow(step.v, 2)) * scene->camera->fov / 2;
	axis = vector3_normalise(new_vector3(step.v, step.u, 0));
//	if (pixel.x == 0 && pixel.y == 0)
//		printf("radius %f step.u %f step.v %f theta %f axis %f %f %f\n", radius, step.u, step.v, theta, axis.x, axis.y, axis.z);
	ray->orientation = vector3_qrotate(new_vector3(0, 0, 1), theta, axis);
	ray->orientation = vector3_rotate_yx(ray->orientation, scene->camera->rotate);
}

//пересчет fov в координаты сцены через кватернионы, где fov == обзору по наибольшей стороне, в таком случае по диагонали обзор > fov
static void	ray_perspective_quaternion2(t_scene *scene, t_xy pixel, t_ray *ray)
{
	double		theta;
	t_vector3	axis;
	double		radius;
	t_vector2	step;

	ray->position = scene->camera->position;
	radius = fmax(scene->width / (double)2, scene->height / (double)2);
	step.u = (pixel.x - scene->width / (double)2) / radius;
	step.v = (pixel.y - scene->height / (double)2) / radius;
	theta = sqrt(pow(step.u, 2) + pow(step.v, 2)) * scene->camera->fov / 2;
	axis = vector3_normalise(new_vector3(step.v, step.u, 0));
//	if (pixel.x == 0 && pixel.y == 0)
//		printf("radius %f step.u %f step.v %f theta %f axis %f %f %f\n", radius, step.u, step.v, theta, axis.x, axis.y, axis.z);
	ray->orientation = vector3_qrotate(new_vector3(0, 0, 1), theta, axis);
	ray->orientation = vector3_rotate_yx(ray->orientation, scene->camera->rotate);
}
// лучи из камеры, поиск места пересечения с фигурами
// в функцию приходит пустой ray, функция считает шаг в отосительных координатах и формирует
static void	raytrace(t_xy pixel, t_ray *ray, t_scene *scene)
{
	t_vector2	step;
	//step -- перевод из координат mlx в координаты сцены (из обсолютных координат пиксельной матрицы, а относительным координатам сцены [-1; 1])
	step = new_vector2((pixel.x - scene->width / (double)2) / scene->width * (double)2, -(pixel.y - scene->height / (double)2) / scene->width * (double)2);
	if (scene->view == 0)
		ray_orthographic(scene->camera, step, ray);
	if (scene->view == 1)
		ray_perspective_tan(scene->camera, step, ray);
	else if (scene->view == 2)
		ray_perspective_spherise(scene->camera, step, ray);
	else if (scene->view == 3)
		ray_perspective_spherise2(scene->camera, step, ray);
	else if (scene->view == 4)
		ray_perspective_spherise3(scene->camera, step, ray);
	else if (scene->view == 5)
		ray_perspective_quaternion(scene, pixel, ray);
	else if (scene->view == 6)
		ray_perspective_quaternion2(scene, pixel, ray);
	intersect(ray, scene);
}

// включает поворот камеры, если флаг play активирован
static void	animate(t_scene *scene)
{
	t_vector2	q;

	q = scene->camera->rotate;
	if (scene->play)
	{
		scene->everynframe = scene->minquality;
		scene->idle = 0;
		if (q.v >= 360 && q.u < 720 && q.v < 720)
		{
			q.u += 10;
			q.v += 10;
		} else if (q.u == 360)
			q.v += 10;
		else if (q.u < 720 && q.v < 720)
			q.u += 10;
		else
		{
			q.u = 0;
			q.v = 0;
			scene->play = FALSE;
		}
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

static	void update_window(t_scene *scene)
{
	if (!scene->oddframe)
	{
		mlx_put_image_to_window(scene->mlx, scene->window, scene->img->img, 0, 0);
		scene->oddframe = 1;
	}
	else
	{
		mlx_put_image_to_window(scene->mlx, scene->window, scene->img2->img, 0, 0);
		scene->oddframe = 0;
	}
	hud(scene);
}

int	render_next_frame(t_scene *scene)
{
	t_xy	pixel;
	t_ray	ray;
	long	time1;
	long	time2;

	animate(scene);
	if (scene->idle > 0)
	{
		scene->idle--;
		return (0);
	}
	else if (scene->idle < 0)
		return (0);
	scene->width = scene->win_w / scene->everynframe;
	if (scene->win_w % scene->everynframe)
		scene->width++;
	scene->height = scene->win_h / scene->everynframe;
	if (scene->win_h % scene->everynframe)
		scene->height++;
	time1 = mtv();
	kd_free(scene->hud);
//	scene->hud = kd_strf("x %d y %d", (int)scene->camera->rotate.u, (int)scene->camera->rotate.v);
	pixel.y = 0;
	while (pixel.y < scene->height)
	{
		pixel.x = 0;
		while (pixel.x < scene->width)
		{
			kd_memset(&ray, 0, sizeof(t_ray));
			raytrace(pixel, &ray, scene);
			draw_pixel(scene, pixel.x, pixel.y, compute_light(&ray, scene));
			pixel.x++;
		}
		pixel.y++;
	}
	time2 = mtv() - time1;
	scene->hud = kd_strf("quality %d/%d view %d fov %d zoom %d frame %dms", scene->everynframe, scene->minquality, scene->view, (int)scene->camera->fov, (int)scene->camera->zoom, (int)time2);
	update_window(scene);
	scene->idle = 1;
	if (scene->everynframe >= 20)
		scene->everynframe /= 2;
	else if (scene->everynframe > 10)
		scene->everynframe = 10;
	else if (scene->everynframe > 1)
		scene->everynframe--;
	else
		scene->idle = -1;
	return (0);
}
