/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   views.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/12 14:53:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//вид без перспективы (ортографический)
void ray_orthographic(t_camera *camera, t_vector2 step, t_ray *ray)
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
void ray_perspective_tan(t_camera *camera, t_vector2 step, t_ray *ray)
{
	ray->position = camera->position;
	ray->orient = new_vector3(tan(camera->fov / 2 * (M_PI / 180))
							  * step.u, tan(camera->fov / 2 * (M_PI / 180)) * step.v, 1);
	ray->orient = vector3_normalise(ray->orient);
	ray->orient = vector3_rotate_yx(ray->orient, camera->rotate);
}

//пересчет fov в координаты сцены через сферу
void	ray_perspective_spherise(t_camera *camera, t_vector2 step, t_ray *ray)
{
	ray->position = camera->position;
	step.v = camera->fov / 2 * step.v;
	step.u = camera->fov / 2 * step.u;
	ray->orient = vector3_rotate_yx(new_vector3(0, 0, 1), step);
	ray->orient = vector3_rotate_yx(ray->orient, camera->rotate);
}

//пересчет fov в координаты сцены через с глобальной поправкой искажения
void	ray_perspective_spherise2(t_camera *camera, t_vector2 step, t_ray *ray)
{
	ray->position = camera->position;
	step.v = camera->fov / 2 * step.v * (0.5 + 0.5 * cos(M_PI_2 * fabs(step.u)));
	step.u = camera->fov / 2 * step.u;
	ray->orient = vector3_rotate_yx(new_vector3(0, 0, 1), step);
	ray->orient = vector3_rotate_yx(ray->orient, camera->rotate);
}

//пересчет fov в координаты сцены через складывание векторов по 2 осям
void	ray_perspective_spherise3(t_camera *camera, t_vector2 step, t_ray *ray)
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
void	ray_perspective_quaternion(t_scene *scene, int x, int y, t_ray *ray)
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
void	ray_perspective_quaternion2(t_scene *scene, int x, int y, t_ray *ray)
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
