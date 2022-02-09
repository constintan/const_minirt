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
