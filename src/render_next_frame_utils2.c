/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/12 14:52:18 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	math_quadratic_equation(t_quad *q)
{
	q->t1 = 0;
	q->t2 = 0;
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

void	intersect_disc(t_disc *disc, t_ray *ray, t_scene *scene)
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
	if (vector3_sumpow2(matrix3_subtract(
				tmp_ray.coordinates, disc->position)) > pow(disc->radius, 2))
		return ;
	*ray = tmp_ray;
}

void	intersect2(t_ray *ray, t_scene *scene)
{
	t_cone		*cone;
	t_cylinder	*cylinder;

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

void	intersect(t_ray *ray, t_scene *scene)
{
	t_plane		*plane;
	t_sphere	*sphere;

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
	intersect2(ray, scene);
}
