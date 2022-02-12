/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:30:30 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/12 16:02:37 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// q.d < 0 нет пересечений, [t1,t2] < 0 отрезает заднее отзеркаливание
// || удаляет результат если ранее был найден объект с пересечением ближе конуса
// отрезает конус-двойник
// ограничевает конус по высоте
void	intersect_cone(t_cone *cone, t_ray *ray, t_scene *scene)
{
	t_ray		tmp_ray;
	t_quad		q;
	t_vector3	v_c2r;

	intersect_disc(&cone->cap, ray, scene);
	v_c2r = matrix3_subtract(ray->position, cone->position);
	q.a = pow(vector3_scalar(ray->orient, cone->orient), 2)
		- cone->pow2costheta;
	q.b = 2 * (vector3_scalar(ray->orient, cone->orient) * vector3_scalar(v_c2r,
				cone->orient) - vector3_scalar(ray->orient, v_c2r)
			* cone->pow2costheta);
	q.c = pow(vector3_scalar(v_c2r, cone->orient), 2) - vector3_scalar(v_c2r,
			v_c2r) * cone->pow2costheta;
	tmp_ray = *ray;
	tmp_ray.t = math_quadratic_equation(&q);
	if (q.t1 > EPSILON && q.t2 > EPSILON && vector3_scalar(ray->orient,
			cone->orient) > 0)
		tmp_ray.t = q.t2;
	if (tmp_ray.t < EPSILON || tmp_ray.t + EPSILON > ray->t)
		return ;
	tmp_ray.coordinates = matrix3_addition(ray->position, vector3_multiply(
				ray->orient, tmp_ray.t));
	if (!(cone->theta < M_PI_2 && vector3_scalar(matrix3_subtract(
					tmp_ray.coordinates, cone->position), cone->orient)
			> -EPSILON))
		return ;
	if (vector3_sumpow2(matrix3_subtract(tmp_ray.coordinates, cone->position))
		> pow(cone->height / cone->costheta, 2))
		return ;
	*ray = tmp_ray;
	ray->normal = vector3_normalise(matrix3_subtract(ray->coordinates,
				matrix3_addition(cone->position, vector3_multiply(
						cone->orient, vector3_distance(ray->coordinates,
							cone->position) / cone->costheta))));
	ray->color = cone->color;
}

void	add_cone_props(t_cone *cone, char *str)
{
	double	height;
	t_color	color;
	int		err;

	err = 0;
	height = ft_atof(&str, &err);
	color = new_color_atoc(&str, &err);
	check_endline(&str, &err);
	if (err)
		ft_error(9);
	cone->height = height;
	cone->color = color;
	cone->cap.position = matrix3_addition(cone->position,
			vector3_multiply(cone->orient, cone->height));
	cone->cap.orient = cone->orient;
	cone->cap.radius = cone->radius;
	cone->cap.color = cone->color;
	cone->theta = atan(cone->radius / cone->height);
	cone->costheta = cos(cone->theta);
	cone->pow2costheta = pow(cone->costheta, 2);
}

void	add_cone(t_scene *scene, char *str)
{
	t_cone		*cone;
	t_vector3	position;
	t_vector3	orient;
	double		diametr;
	int			err;

	err = 0;
	position = new_vector_atof(&str, &err);
	orient = new_vector_atof(&str, &err);
	check_direction_limits(orient, &err);
	diametr = ft_atof(&str, &err);
	if (err)
		ft_error(9);
	cone = new_cone(position, orient, diametr / 2);
	add_cone_props(cone, str);
	cone->next = scene->cones;
	scene->cones = cone;
}

t_cone	*new_cone(t_vector3 position, t_vector3 orient, double radius)
{
	t_cone	*cone;

	cone = kd_calloc(1, sizeof(t_cone));
	if (cone == NULL)
		ft_error(-1);
	cone->position = position;
	cone->orient = vector3_normalise(orient);
	cone->radius = radius;
	return (cone);
}
