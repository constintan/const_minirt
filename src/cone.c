/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:30:30 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/07 11:17:04 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_cone(t_scene *scene, char *str)
{
	t_cone	*cone;
	t_vector3	position;
	t_vector3	orient;
	double		diametr;
	double		height;
	t_color		color;
	int			err;

	err = 0;
	position = new_vector_atof(&str, &err);
	printf("***add_cone***\n");
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
	cone = new_cone(position, orient, diametr / 2, height, color);
	cone->next = scene->cones;
	scene->cones = cone;

	// return (1);
}

t_cone		*new_cone(t_vector3 position, t_vector3 orient, double radius, double height, t_color color)
{
	t_cone	*cone;

	cone = kd_calloc(1, sizeof(t_cone));
	if (cone == NULL)
		ft_error(-1);
	cone->position = position;
	cone->orient = vector3_normalise(orient);
	cone->radius = radius;
	cone->height = height;
	cone->color = color;
	cone->cap.position = matrix3_addition(cone->position, vector3_multiply(cone->orient, cone->height));
	cone->cap.orient = cone->orient;
	cone->cap.radius = cone->radius;
	cone->cap.color = cone->color;
	cone->theta = atan(cone->radius / cone->height);
	cone->costheta = cos(cone->theta);
	cone->pow2costheta = pow(cone->costheta, 2);
	return (cone);
}