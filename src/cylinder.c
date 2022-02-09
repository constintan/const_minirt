/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:30:30 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/01 22:16:53 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_cylinder(t_scene *scene, char *str)
{
	t_cylinder	*cylinder;
	t_vector3	position;
	t_vector3	orient;
	double		diametr;
	double		height;
	t_color		color;
	int			err;

	err = 0;
	position = new_vector_atof(&str, &err);
	printf("***add_cylinder***\n");
	printf("position.x:%f\n", position.x);
	printf("err:%d\n", err);
	printf("position.y:%f\n", position.y);
	printf("err:%d\n", err);
	printf("position.z:%f\n", position.z);
	printf("err:%d\n", err);

	orient = new_vector_atof(&str, &err);
	printf("orient.x:%f\n", orient.x);
	printf("err:%d\n", err);
	printf("orient.y:%f\n", orient.y);
	printf("err:%d\n", err);
	printf("orient.z:%f\n", orient.z);
	printf("err:%d\n", err);

	check_direction_limits(orient, &err);
	printf("err:%d\n", err);

	diametr = ft_atof(&str, &err);
	printf("diametr:%f\n", diametr);
	printf("err:%d\n", err);

	height = ft_atof(&str, &err);
	printf("height:%f\n", height);
	printf("err:%d\n", err);

	color = new_color_atoc(&str, &err);
	printf("color->r:%d\n", color.r);
	printf("color->g:%d\n", color.g);
	printf("color->b:%d\n", color.b);

	printf("err:%d\n", err);
	check_endline(&str, &err);
	printf("err:%d\n", err);
	if (err)
		ft_error(9);
	cylinder = new_cylinder(position, orient, diametr / 2, height, color);
	cylinder->next = scene->cylinders;
	scene->cylinders = cylinder;

}

t_cylinder	*new_cylinder(t_vector3 position, t_vector3 orient, double radius, double height, t_color color)
{
	t_cylinder	*cylinder;

	cylinder = kd_calloc(1, sizeof(t_cylinder));
	if (cylinder == NULL)
		ft_error(-1);
	cylinder->position = position;
	cylinder->orient = vector3_normalise(orient);
	cylinder->radius = radius;
	cylinder->height = height;
	cylinder->color = color;
	cylinder->cap_bot.position = cylinder->position;
	cylinder->cap_bot.orient = vector3_negate(cylinder->orient);
	cylinder->cap_bot.radius = cylinder->radius;
	cylinder->cap_bot.color = cylinder->color;
	cylinder->cap_top.position = matrix3_addition(cylinder->position, vector3_multiply(cylinder->orient, cylinder->height));
	cylinder->cap_top.orient = cylinder->orient;
	cylinder->cap_top.radius = cylinder->radius;
	cylinder->cap_top.color = cylinder->color;
	return (cylinder);
}

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
	q->a = vector3_sumpow2(matrix3_subtract(
				ray->orient, vector3_multiply(cylinder->orient,
					vector3_scalar(ray->orient,
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
