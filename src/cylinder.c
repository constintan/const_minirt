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

t_cylinder		*new_cylinder(t_vector3 position, t_vector3 orient, double radius, double height, t_color color)
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
	return (cylinder);
}

void	intersect_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	t_ray	result_ray;
	t_ray	tmp_ray;
	t_plane	cap;

	cap.position = cylinder->position;
	cap.orient = cylinder->orient;
	cap.color = cylinder->color;
	result_ray = *ray;
	tmp_ray = *ray;
	intersect_plane(&cap, &tmp_ray);
	if (tmp_ray.distance)
	{
		if (vector3_sumpow2(matrix3_subtract(tmp_ray.coordinates, cap.position)) <= pow(cylinder->radius, 2))
		{//			if (vector3_scalar(new_ray.orientation, cap1.orient) < 0)
			result_ray = tmp_ray;
//				return ;
		}
	}
	tmp_ray = *ray;
	cap.position = matrix3_addition(cylinder->position, vector3_multiply(cylinder->orient, cylinder->height));
	cap.orient = cylinder->orient;
	cap.color = cylinder->color;
	intersect_plane(&cap, &tmp_ray);
	if (tmp_ray.distance)
	{
		if (vector3_sumpow2(matrix3_subtract(tmp_ray.coordinates, cap.position)) <= pow(cylinder->radius, 2))
		{//			if (vector3_scalar(new_ray.orientation, cap1.orient) < 0)
			if (tmp_ray.distance < result_ray.distance || result_ray.distance < EPSILON)
			{
				result_ray = tmp_ray;
			}
//			return ;
		}
	}

	t_vector3 p;
	t_quad q;

	tmp_ray = *ray;
	p = matrix3_subtract(tmp_ray.position, cylinder->position);
	q.a = vector3_sumpow2(matrix3_subtract(tmp_ray.orientation,
										   vector3_multiply(
												   cylinder->orient,
												   vector3_scalar(
														   tmp_ray.orientation,
														   cylinder->orient))));
	q.b = 2 * (vector3_scalar(matrix3_subtract(tmp_ray.orientation,
											   vector3_multiply(
													   cylinder->orient,
													   vector3_scalar(
															   tmp_ray.orientation,
															   cylinder->orient))),
							  matrix3_subtract(p, vector3_multiply(
									  cylinder->orient,
									  vector3_scalar(p,
													 cylinder->orient)))));
	q.c = vector3_sumpow2(
			matrix3_subtract(p, vector3_multiply(cylinder->orient,
												 vector3_scalar(p,
																cylinder->orient)))) -
		  pow(cylinder->radius, 2);
	q.d = math_discriminant(q.a, q.b, q.c);
	*ray = result_ray;
	if (q.d < 0)
		return;
	tmp_ray.t = (-q.b + sqrt(q.d)) / (2 * q.a);
	if (tmp_ray.t < EPSILON)
		tmp_ray.t = (-q.b - sqrt(q.d)) / (2 * q.a);
		//может ли здесь быть меньше нуля ?
	if (tmp_ray.distance > result_ray.distance)
		return;

	/*проверка что оно лежит внутри **обрезанного** цилиндра*/
	t_vector3 qq = matrix3_addition(tmp_ray.position, vector3_multiply(tmp_ray.orientation, tmp_ray.t));
	if (vector3_scalar(cylinder->orient, matrix3_subtract(qq, cylinder->position)) <= 0)
		return;
	if (vector3_scalar(cylinder->orient,
					   matrix3_subtract(qq,
										cap.position)) >= EPSILON)
		return;

	tmp_ray.coordinates = matrix3_addition(ray->position, vector3_multiply(
			ray->orientation, tmp_ray.t));
	tmp_ray.distance = vector3_distance(ray->position, tmp_ray.coordinates);
//		if (tmp_ray.distance < EPSILON || (ray->distance < tmp_ray.distance && ray->distance))
//			return ; //зачеееем
	*ray = tmp_ray;

/*подсчет нормали 1 вариант*/

//	t = dot((hit_pt - cy.bottom_center), cy.ori); // cy.ori should be normalized and so has the length of 1.
//	pt = cy.bottom_center + t * cy.ori;
//	surface_normal = normalize(hit_pt - pt)));

//	double t = vector3_scalar(matrix3_subtract(tmp_ray.coordinates, cylinder->position), cylinder->orient); // cy.ori should be normalized and so has the length of 1.
//	t_vector3 pt = matrix3_addition(cylinder->position, vector3_multiply(cylinder->orient, t));
//	ray->normal = vector3_normalise(matrix3_subtract(tmp_ray.coordinates, pt));
//	printf("ray->normal:%f\n", vec_length(ray->normal));

/*подсчет нормали 2 вариант*/

	t_vector3 op = matrix3_subtract(ray->coordinates, cylinder->position);
	ray->normal = matrix3_subtract(op, vector3_multiply(cylinder->orient, vector3_scalar(cylinder->orient, op)));

	ray->color = cylinder->color;
	ray->color = new_color(200,200,200);

}