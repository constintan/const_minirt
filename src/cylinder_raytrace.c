/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_raytrace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:30:30 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/01 22:16:53 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_in_cutted_cylinder(t_cylinder *cylinder, t_ray *ray, t_quad q)
{
	t_vector3	qq;

	qq = matrix3_addition(ray->position, vector3_multiply(ray->orient, ray->t));
	if ((vector3_scalar(cylinder->orient, matrix3_subtract(qq,
					cylinder->cap_bot.position)) > 0) && (vector3_scalar(
				cylinder->orient, matrix3_subtract(qq,
					cylinder->cap_top.position)) < 0))
		return (1);
	if (q.t2 == 0)
		return (0);
	ray->t = q.t2;
	qq = matrix3_addition(ray->position, vector3_multiply(ray->orient, ray->t));
	if ((vector3_scalar(cylinder->orient, matrix3_subtract(qq,
					cylinder->cap_bot.position)) > 0) && (vector3_scalar(
				cylinder->orient, matrix3_subtract(qq,
					cylinder->cap_top.position)) < 0))
		return (1);
	return (0);
}

void	init_cylinder_q(t_cylinder *cylinder, t_ray	*ray, t_quad *q)
{
	t_vector3	p;

	p = matrix3_subtract(ray->position, cylinder->position);
	q->a = vector3_sumpow2(matrix3_subtract(ray->orient, vector3_multiply(
					cylinder->orient, vector3_scalar(ray->orient,
						cylinder->orient))));
	q->b = 2 * (vector3_scalar(matrix3_subtract(ray->orient,
					vector3_multiply(cylinder->orient, vector3_scalar(
							ray->orient, cylinder->orient))),
				matrix3_subtract(p, vector3_multiply(cylinder->orient,
						vector3_scalar(p, cylinder->orient)))));
	q->c = vector3_sumpow2(matrix3_subtract(p, vector3_multiply(
					cylinder->orient, vector3_scalar(p, cylinder->orient))))
		- pow(cylinder->radius, 2);
}

void	intersect_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	t_ray		tmp_ray;
	t_quad		q;
	t_vector3	op;

	intersect_disc(&cylinder->cap_bot, ray);
	intersect_disc(&cylinder->cap_top, ray);
	tmp_ray = *ray;
	init_cylinder_q(cylinder, &tmp_ray, &q);
	tmp_ray.t = math_quadratic_equation(&q);
	if (tmp_ray.t < EPSILON || tmp_ray.t + EPSILON > ray->t)
		return ;
	if (is_in_cutted_cylinder(cylinder, &tmp_ray, q) != 1)
		return ;
	if (tmp_ray.t < EPSILON || tmp_ray.t + EPSILON > ray->t)
		return ;
	tmp_ray.coordinates = matrix3_addition(ray->position, vector3_multiply(
				ray->orient, tmp_ray.t));
	*ray = tmp_ray;
	op = matrix3_subtract(ray->coordinates, cylinder->position);
	ray->normal = vector3_normalise(matrix3_subtract(op,
				vector3_multiply(cylinder->orient,
					vector3_scalar(cylinder->orient, op))));
	ray->color = cylinder->color;
}
