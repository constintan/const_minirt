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

//пересчет fov в координаты сцены через кватернионы, где fov == обзору по
// диагонали
void	ray_perspective_quaternion(t_scene *scene, int x, int y, t_ray *ray)
{
	double		theta;
	t_vector3	axis;
	double		radius;
	t_vector2	step;

	ray->position = scene->camera->position;
	radius = sqrt(pow(scene->width / (double)2, 2) + pow(scene->height
				/ (double)2, 2));
	step.u = (x - scene->width / (double)2) / radius;
	step.v = (y - scene->height / (double)2) / radius;
	theta = sqrt(pow(step.u, 2) + pow(step.v, 2)) * scene->camera->fov / 2;
	axis = vector3_normalise(new_vector3(step.v, step.u, 0));
	ray->orient = vector3_qrotate(new_vector3(0, 0, 1), theta, axis);
	ray->orient = vector3_rotate_yx(ray->orient, scene->camera->rotate);
}

//пересчет fov в координаты сцены через кватернионы, где fov == обзору по
// наибольшей стороне, в таком случае по диагонали обзор > fov
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
	ray->orient = vector3_qrotate(new_vector3(0, 0, 1), theta, axis);
	ray->orient = vector3_rotate_yx(ray->orient, scene->camera->rotate);
}
