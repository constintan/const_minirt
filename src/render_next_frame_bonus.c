/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/12 00:14:12 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minirt_bonus.h"

double	math_discriminant(double a, double b, double c)
{
	return (pow(b, 2) - 4 * a * c);
}

double	math_quadratic_equation(t_quad *q)
{
	q->d = pow(q->b, 2) - 4 * q->a * q->c;
	if (q->d < 0 && q->d > -EPSILON)
		q->d = 0;
	if (q->d < 0)
		return (-1);
	q->sqrt_d = sqrt(q->d);
	q->t1 = (-q->b - q->sqrt_d) / (2 * q->a);
	q->t2 = (-q->b + q->sqrt_d) / (2 * q->a);
	if (fmin(q->t1, q->t2) > EPSILON)
		return (fmin(q->t1, q->t2));
	return (fmax(q->t1, q->t2));
}

static void	texture_plane(t_plane *plane, t_ray *ray, t_bool bump, t_scene *scene)
{
	char	*dst;
	t_vector3	un;
	t_vector3	vn;
	t_vector3	local;
	t_vector3	ulocal;
	double		costheta;
	t_vector2	tile;
	t_vector3	color;
	char	*ddd;

	if (!bump)
		return ;
	un = vector3_cw(plane->orient);
	local = matrix3_subtract(ray->coordinates, plane->position);
	ulocal = vector3_normalise(local);
	costheta = vector3_scalar(ulocal, un);
	tile.u = sqrt(vector3_sumpow2(local)) * costheta * 100;
	vn = vector3_ccw(plane->orient);
	costheta = vector3_scalar(ulocal, vn);
	tile.v = sqrt(vector3_sumpow2(local)) * costheta * 100;
//	if (fmod(floor(fmod(tile.u, scene->bumpmap->width)), scene->bumpmap->width))
//	{
		ddd = scene->texturemap->addr + ((int)fmod(fmod(tile.v, scene->bumpmap->height) + scene->bumpmap->height, scene->bumpmap->height) * scene->bumpmap->bytes_per_line + (int)fmod(fmod(tile.u, scene->bumpmap->width) + scene->bumpmap->width, scene->bumpmap->width) * (scene->bumpmap->bits_per_pixel / 8));
		dst = scene->bumpmap->addr + ((int)fmod(fmod(tile.v, scene->bumpmap->height) + scene->bumpmap->height, scene->bumpmap->height) * scene->bumpmap->bytes_per_line + (int)fmod(fmod(tile.u, scene->bumpmap->width) + scene->bumpmap->width, scene->bumpmap->width) * (scene->bumpmap->bits_per_pixel / 8));
//		printf("tile.u %f tile.v %f\n", tile.u, tile.v);
		ray->color = new_color((*(unsigned int *)ddd & 0x00ff0000) >> 16, (*(unsigned int *)ddd & 0x0000ff00) >> 8, (*(unsigned int *)ddd & 0x000000ff));
		color = new_vector3((*(unsigned int *)dst & 0x00ff0000) >> 16, (*(unsigned int *)dst & 0x0000ff00) >> 8, (*(unsigned int *)dst & 0x000000ff));
		color.x = (color.x / 255 - 0.5) * 2;
		color.y = (color.y / 255 - 0.5) * 2;
		color.z = (color.z / 255 - 0.5) * 2;
		ray->normal = vector3_qrotate(vector3_qrotate(ray->normal, color.y * 90, un), color.x * -90, vn);
//		printf("r %f g %f b %f\n", color.x, color.y, color.z);
//	}
}

//https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
void	intersect_plane(t_plane *plane, t_ray *ray, t_bool bump, t_scene *scene)
{
	double		denominator;
	double		distance;

	denominator = vector3_scalar(plane->orient, ray->orient);
	if (denominator > EPSILON)
	{
		distance = vector3_scalar(matrix3_subtract(plane->position, ray->position), plane->orient) / denominator;
		if (distance < EPSILON || (distance + EPSILON > ray->t))
			return ;
		ray->normal = vector3_negate(plane->orient);
	}
	else if (denominator < -EPSILON)
	{
		denominator = vector3_scalar(vector3_negate(plane->orient), ray->orient);
		distance = vector3_scalar(matrix3_subtract(plane->position, ray->position), vector3_negate(plane->orient)) / denominator;
		if (distance < EPSILON || (distance + EPSILON > ray->t))
			return ;
		ray->normal = plane->orient;
	}
	else
		return ;
	ray->t = distance;
	ray->coordinates = matrix3_addition(ray->position, vector3_multiply(ray->orient, distance));
	ray->color = plane->color;
	texture_plane(plane, ray, bump, scene);
}

void intersect_disc(t_disc *disc, t_ray *ray, t_scene *scene)
{
	t_ray	tmp_ray;
	t_plane	plane;

	plane.position = disc->position;
	plane.orient = disc->orient;
	plane.color = disc->color;
	tmp_ray = *ray;
	intersect_plane(&plane, &tmp_ray, FALSE, scene);
	if (tmp_ray.t + EPSILON > ray->t)
		return ;
	if (vector3_sumpow2(matrix3_subtract(tmp_ray.coordinates, disc->position)) > pow(disc->radius, 2))
		return ;
	*ray = tmp_ray;
}

static void	intersect_cone(t_cone *cone, t_ray *ray, t_scene *scene)
{
	t_ray		tmp_ray;
	t_quad		q;
	t_vector3	v_c2r;

	intersect_disc(&cone->cap, ray, scene);
	v_c2r = matrix3_subtract(ray->position, cone->position);
	q.a = pow(vector3_scalar(ray->orient, cone->orient), 2) - cone->pow2costheta;
	q.b = 2 * (vector3_scalar(ray->orient, cone->orient) * vector3_scalar(v_c2r, cone->orient) - vector3_scalar(ray->orient, v_c2r) * cone->pow2costheta);
	q.c = pow(vector3_scalar(v_c2r, cone->orient), 2) - vector3_scalar(v_c2r, v_c2r) * cone->pow2costheta;
	tmp_ray = *ray;
	tmp_ray.t = math_quadratic_equation(&q);
	if (q.t1 > EPSILON && q.t2 > EPSILON && vector3_scalar(ray->orient, cone->orient) > 0)
		tmp_ray.t = q.t2;
	if (tmp_ray.t < EPSILON || tmp_ray.t + EPSILON > ray->t)
		return ; // q.d < 0 нет пересечений, [t1,t2] < 0 отрезает заднее отзеркаливание || удаляет результат если ранее был найден объект с пересечением ближе конуса
	tmp_ray.coordinates = matrix3_addition(ray->position, vector3_multiply(ray->orient, tmp_ray.t));
	if (!(cone->theta < M_PI_2 && vector3_scalar(matrix3_subtract(tmp_ray.coordinates, cone->position), cone->orient) > -EPSILON))
		return ; // отрезает конус-двойник
	if (vector3_sumpow2(matrix3_subtract(tmp_ray.coordinates, cone->position)) > pow(cone->height / cone->costheta, 2))
		return ; // ограничевает конус по высоте
	*ray = tmp_ray;
	ray->normal = vector3_normalise(matrix3_subtract(ray->coordinates, matrix3_addition(cone->position, vector3_multiply(cone->orient, vector3_distance(ray->coordinates, cone->position) / cone->costheta))));
	ray->color = cone->color;
}

static void	bump(t_ray *ray, t_scene *scene)
{
	t_vector3		axis;

	return ;
	(void)scene;
	axis = vector3_cw(ray->normal);
//	printf("1n %f %f %f\n", ray->normal.x, ray->normal.y, ray->normal.z);
	ray->normal = vector3_qrotate(ray->normal, 10, axis);
//	printf("2n %f %f %f\n", ray->normal.x, ray->normal.y, ray->normal.z);
}

static t_color	texture_sphere(t_sphere *sphere, t_ray *ray, t_scene *scene)
{
	double	uf;
	double	vf;
	double	u;
	double	v;
	t_color	color;

	if (scene->bump)
		bump(ray, scene);
	if (!scene->checkerboard && !scene->bump)
		return (sphere->color);
	u = 0.5 + atan2((ray->coordinates.z - sphere->position.z) / sphere->radius, (ray->coordinates.x - sphere->position.x) / sphere->radius) / (2 * M_PI);
	v = 0.5 - asin((ray->coordinates.y - sphere->position.y) / sphere->radius) / M_PI;
	uf = floor(fmod(u * 18, 2));
	vf = floor(fmod(v * 9, 2));

	if (scene->bump)
	{
		ray->normal = vector3_qrotate(ray->normal, sin(u * M_PI_2 * 360) * 10,
									  vector3_cw(ray->normal));
		ray->normal = vector3_qrotate(ray->normal, sin(v * M_PI_2 * 180) * 10,
									  vector3_cw(ray->normal));
	}
	color = sphere->color;
	if ((uf && vf) || (!uf && !vf))
	{
		if (scene->checkerboard)
			color = new_color(255, 255, 255);
	}
	else
	{
		if (scene->checkerboard)
			color = new_color(0, 0, 0);
	}
	return (color);
}

//https://www.ccs.neu.edu/home/fell/CS4300/Lectures/Ray-TracingFormulas.pdf
static void	intersect_sphere(t_sphere *sphere, t_ray *ray, t_scene *scene)
{
	t_ray		tmp_ray;
	t_vector3	d;
	t_vector3	p;
	t_quad		q;

	d = ray->orient;
	p = matrix3_subtract(ray->position, sphere->position);
	q.a = vector3_sumpow2(d);
	q.b = 2 * d.x * p.x + 2 * d.y * p.y + 2 * d.z * p.z;
	q.c = vector3_sumpow2(sphere->position) + vector3_sumpow2(ray->position) - 2 * vector3_scalar(sphere->position, ray->position) - pow(sphere->radius, 2);
	tmp_ray = *ray;
	tmp_ray.t = math_quadratic_equation(&q);
	if (tmp_ray.t < EPSILON || tmp_ray.t + EPSILON > ray->t)
		return ;
	*ray = tmp_ray;
	ray->coordinates = matrix3_addition(ray->position, vector3_multiply(d, ray->t));
	if (fmin(q.t1, q.t2) > EPSILON)
		ray->normal = vector3_normalise(matrix3_subtract(ray->coordinates, sphere->position));
	else
		ray->normal = vector3_normalise(matrix3_subtract(sphere->position, ray->coordinates));
	ray->color = texture_sphere(sphere, ray, scene);
}

void	intersect(t_ray *ray, t_scene *scene)
{
	t_plane		*plane;
	t_sphere	*sphere;
	t_cone		*cone;
	t_cylinder 	*cylinder;

	plane = scene->planes;
	while (plane)
	{
		intersect_plane(plane, ray, scene->bump, scene);
		plane = plane->next;
	}
	sphere = scene->spheres;
	while (sphere)
	{
		intersect_sphere(sphere, ray, scene);
		sphere = sphere->next;
	}
	cone = scene->cones;
	while (cone)
	{
		intersect_cone(cone, ray, scene);
		cone = cone->next;
	}
	cylinder = scene->cylinders;
	while (cylinder)
	{
		intersect_cylinder(cylinder, ray, scene);
		cylinder = cylinder->next;
	}
}

static t_bool compute_shadow(t_light *light, t_vector3 l, t_ray *ray, t_scene *scene)
{
	t_ray	new_ray;

	new_ray.position = ray->coordinates;
	new_ray.orient = l;
	new_ray.t = INFINITY;
	intersect(&new_ray, scene);
	if (new_ray.t > EPSILON && pow(new_ray.t, 2) + EPSILON < vector3_sumpow2(matrix3_subtract(light->position, ray->coordinates)))
		return (TRUE);
	return (FALSE);
}

static t_color	apply_light(t_color object, t_color light, double intensity)
{
	return (colour_matrix_amplify(object, colour_amplify(light, intensity)));
}

static void	compute_light(t_ray *ray, t_scene *scene)
{
	t_light		*light;
	t_vector3	l;
	double		fctr;
	t_color		color;
	double		hf;
	t_vector3	h;
	double		n;

//	new_ray = compute_mirror_angle(ray);
//	intersect(new_ray, scene);
//	new_ray == ray из камеры
//	new_ray.color == цвет объекта в отражении шара

//	если пересечений не было, то distance по дефолту = INFINITY
	if (ray->t == INFINITY)
	{
		ray->color = new_color(DEF_BG_COLOR_R, DEF_BG_COLOR_G, DEF_BG_COLOR_B);
		return ;
	}
	color = apply_light(ray->color, scene->ambient->color, scene->ambient->bright);
	light = scene->light;
	while (light && !scene->no_lights)
	{
		if (!scene->one_light || scene->current_light == light)
		{
			l = vector3_normalise(matrix3_subtract(light->position, ray->coordinates));
			fctr = vector3_scalar(ray->normal, l);
			//перпендикулярный нормаль к свету = 0, параллельный = 1
			if (fctr < 0 || (!scene->no_shadows && compute_shadow(light, l, ray, scene)))
				fctr = 0;
			color = colour_add(color, colour_amplify(apply_light(ray->color, light->color, light->bright), fctr));
			//блики
			if (!scene->no_specular && fctr)//vector3_scalar(ray->normal, l) > 0)
			{
				h = vector3_normalise(matrix3_addition(vector3_negate(ray->orient), l));
				n = 16;
				hf = vector3_scalar(h, ray->normal) * sin(M_PI_2 * sin(M_PI_2 * sin(M_PI_2 * sin(M_PI_2 * fctr))));
				if (hf > 0)
					color = colour_add(color, colour_amplify(apply_light(color, light->color, light->bright), pow(hf, n)));
			}
		}
		light = light->next;
	}
	ray->color = colour_gamma_collect(color, scene);
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
	ray->orient = vector3_rotate_yx(new_vector3(0, 0, 1), camera->rotate);
}

//пересчет fov в координаты сцены через тангенс
static void ray_perspective_tan(t_camera *camera, t_vector2 step, t_ray *ray)
{
	ray->position = camera->position;
	ray->orient = new_vector3(tan(camera->fov / 2 * (M_PI / 180))
							  * step.u, tan(camera->fov / 2 * (M_PI / 180)) * step.v, 1);
	ray->orient = vector3_normalise(ray->orient);
	ray->orient = vector3_rotate_yx(ray->orient, camera->rotate);
}

//пересчет fov в координаты сцены через сферу
static void	ray_perspective_spherise(t_camera *camera, t_vector2 step, t_ray *ray)
{
	ray->position = camera->position;
	step.v = camera->fov / 2 * step.v;
	step.u = camera->fov / 2 * step.u;
	ray->orient = vector3_rotate_yx(new_vector3(0, 0, 1), step);
	ray->orient = vector3_rotate_yx(ray->orient, camera->rotate);
}

//пересчет fov в координаты сцены через с глобальной поправкой искажения
static void	ray_perspective_spherise2(t_camera *camera, t_vector2 step, t_ray *ray)
{
	ray->position = camera->position;
	step.v = camera->fov / 2 * step.v * (0.5 + 0.5 * cos(M_PI_2 * fabs(step.u)));
	step.u = camera->fov / 2 * step.u;
	ray->orient = vector3_rotate_yx(new_vector3(0, 0, 1), step);
	ray->orient = vector3_rotate_yx(ray->orient, camera->rotate);
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
	ray->orient = vector3_rotate_yx(vector3_normalise(matrix3_addition(tempx, tempy)), camera->rotate);
}

//пересчет fov в координаты сцены через кватернионы, где fov == обзору по диагонали
static void	ray_perspective_quaternion(t_scene *scene, int x, int y, t_ray *ray)
{
	double		theta;
	t_vector3	axis;
	double		radius;
	t_vector2	step;

	ray->position = scene->camera->position;
	radius = sqrt(pow(scene->width / (double)2, 2) + pow(scene->height / (double)2, 2));
	step.u = (x - scene->width / (double)2) / radius;
	step.v = (y - scene->height / (double)2) / radius;
	theta = sqrt(pow(step.u, 2) + pow(step.v, 2)) * scene->camera->fov / 2;
	axis = vector3_normalise(new_vector3(step.v, step.u, 0));
//	if (pixel.x == 0 && pixel.y == 0)
//		printf("radius %f step.u %f step.v %f theta %f axis %f %f %f\n", radius, step.u, step.v, theta, axis.x, axis.y, axis.z);
	ray->orient = vector3_qrotate(new_vector3(0, 0, 1), theta, axis);
	ray->orient = vector3_rotate_yx(ray->orient, scene->camera->rotate);
}

//пересчет fov в координаты сцены через кватернионы, где fov == обзору по наибольшей стороне, в таком случае по диагонали обзор > fov
static void	ray_perspective_quaternion2(t_scene *scene, int x, int y, t_ray *ray)
{
	double		theta;
	t_vector3	axis;
	double		radius;
	t_vector2	step;

	ray->position = scene->camera->position;
	radius = fmax(scene->width / (double)2, scene->height / (double)2);
	step.u = (x - scene->width / (double)2) / radius;
	step.v = (y - scene->height / (double)2) / radius;
	theta = sqrt(pow(step.u, 2) + pow(step.v, 2)) * scene->camera->fov / 2;
	axis = vector3_normalise(new_vector3(step.v, step.u, 0));
//	if (pixel.x == 0 && pixel.y == 0)
//		printf("radius %f step.u %f step.v %f theta %f axis %f %f %f\n", radius, step.u, step.v, theta, axis.x, axis.y, axis.z);
	ray->orient = vector3_qrotate(new_vector3(0, 0, 1), theta, axis);
	ray->orient = vector3_rotate_yx(ray->orient, scene->camera->rotate);
}
// лучи из камеры, поиск места пересечения с фигурами
// в функцию приходит пустой ray, функция считает шаг в отосительных координатах и формирует
void	raytrace(int x, int y, t_ray *ray, t_scene *scene)
{
	t_vector2	step;
	//step -- перевод из координат mlx в координаты сцены (из обсолютных координат пиксельной матрицы, а относительным координатам сцены [-1; 1])
	step = new_vector2((x - scene->width / (double)2) / scene->width * (double)2, -(y - scene->height / (double)2) / scene->width * (double)2);
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
		ray_perspective_quaternion(scene, x, y, ray);
	else if (scene->view == 6)
		ray_perspective_quaternion2(scene, x, y, ray);
	intersect(ray, scene);
}

// включает поворот камеры, если флаг play активирован
static void	animate(t_scene *scene)
{
	static t_vector2			q;

	if (scene->play)
	{
//		printf("c u %f v %f\n", scene->camera->rotate.u, scene->camera->rotate.v);
		scene->everynframe = scene->minquality;
		scene->idle = 0;
		scene->rays_set = FALSE;
		if (q.v >= 360 && q.u < 720 && q.v < 720)
		{
			rotate_camera_xz(scene->camera, -10);
			rotate_camera_y(scene->camera, 10);
			q.u += 10;
			q.v += 10;
		} else if (q.u == 360)
		{
			rotate_camera_xz(scene->camera, -10);
			q.v += 10;
		}
		else if (q.u < 720 && q.v < 720)
		{
			rotate_camera_y(scene->camera, 10);
			q.u += 10;
		}
		else
		{
			q.u = 0;
			q.v = 0;
			scene->play = FALSE;
		}
	}
	else
	{
		q.u = 0;
		q.v = 0;
	}
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

static void	iterate_pixels(t_scene *scene, t_thread *thread)
{
	t_ray	*ray;
	int		x;
	int		y;

	y = thread->index * scene->everynframe;
	while (y < scene->height)
	{
		x = 0;
		while (x < scene->width)
		{
			ray = &scene->rays[y * scene->width + x];
			if (x % scene->everynframe == 0 &&
				y % scene->everynframe == 0)
			{
				if (!ray->t)
				{
					ray->t = INFINITY;
					raytrace(x, y, ray, scene);
					compute_light(ray, scene);
				}
			}
			x++;
		}
		y = y + THREADS * scene->everynframe;
	}
}

static void	iterate_pixels_gamma_correction(t_scene *scene)
{
	t_ray	*ray;
	int		x;
	int		y;

	y = 0;
	while (y < scene->height)
	{
		x = 0;
		while (x < scene->width)
		{
			ray = &scene->rays[y * scene->width + x];
			if (x % scene->everynframe == 0 &&
				y % scene->everynframe == 0)
				draw_pixel(scene, x, y, colour_gamma_apply(ray->color, scene));
			x++;
		}
		y++;
	}
}

static void	reset_rays(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->width * scene->height)
		scene->rays[i++].t = 0;
	scene->rays_set = TRUE;
}

void	*thread_loop(void *thread_void)
{
	t_scene *scene;
	t_thread *thread;
	t_bonus *bonus;

	thread = thread_void;
	scene = thread->scene;
	bonus = scene->bonus;
	while (1)
	{
//		printf("1\n");
		sem_wait(bonus->threads1);
//		printf("2\n");
		sem_post(bonus->threads2);
//		printf("3\n");
		iterate_pixels(scene, thread);
//		printf("4\n");
		sem_wait(bonus->threads3);
//		printf("5\n");
		sem_post(bonus->threads4);
//		printf("6\n");
	}
	return (NULL);
}

int	render_next_frame_bonus(t_scene *scene)
{
	int	i;
	t_bonus	*bonus;

//	printf("THREADS %d\n", THREADS);
//	exit(0);
//	printf("a\n");
	bonus = scene->bonus;
//	printf("b\n");
	animate(scene);
//	printf("c\n");
	if (scene->idle > 0)
	{
		scene->idle--;
		return (0);
	}
	else if (scene->idle < 0)
		return (0);
//	printf("d\n");
	bonus->timestamp = mtv();
//	printf("e\n");
	if (!scene->rays_set)
		reset_rays(scene);
//	printf("f\n");
	i = 0;
	while (i++ < THREADS)
		sem_post(bonus->threads1);
//	printf("g\n");
	i = 0;
	while (i++ < THREADS)
		sem_wait(bonus->threads2);
//	printf("h\n");
	i = 0;
	while (i++ < THREADS)
		sem_post(bonus->threads3);
//	printf("i\n");
	i = 0;
	while (i++ < THREADS)
		sem_wait(bonus->threads4);
//	printf("j\n");
	iterate_pixels_gamma_correction(scene);
//	printf("k\n");
	update_window(scene);
//	printf("l\n");
	scene->idle = 1;
//	printf("m\n");
	if (scene->everynframe >= 20)
		scene->everynframe /= 2;
	else if (scene->everynframe > 10)
		scene->everynframe = 10;
	else if (scene->everynframe > scene->maxquality)
		scene->everynframe--;
	else
		scene->idle = -1;
//	printf("n\n");
	return (0);
}
