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

void	add_cylinder_props(t_cylinder *cylinder, char *str)
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
	cylinder->height = height;
	cylinder->color = color;
	cylinder->cap_bot.position = cylinder->position;
	cylinder->cap_bot.orient = vector3_negate(cylinder->orient);
	cylinder->cap_bot.radius = cylinder->radius;
	cylinder->cap_bot.color = cylinder->color;
	cylinder->cap_top.position = matrix3_addition(cylinder->position,
			vector3_multiply(cylinder->orient, cylinder->height));
	cylinder->cap_top.orient = cylinder->orient;
	cylinder->cap_top.radius = cylinder->radius;
	cylinder->cap_top.color = cylinder->color;
}

void	add_cylinder(t_scene *scene, char *str)
{
	t_cylinder	*cylinder;
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
	cylinder = new_cylinder(position, orient, diametr / 2);
	add_cylinder_props(cylinder, str);
	cylinder->next = scene->cylinders;
	scene->cylinders = cylinder;
}

t_cylinder	*new_cylinder(t_vector3 position, t_vector3 orient, double radius)
{
	t_cylinder	*cylinder;

	cylinder = kd_calloc(1, sizeof(t_cylinder));
	if (cylinder == NULL)
		ft_error(-1);
	cylinder->position = position;
	cylinder->orient = vector3_normalise(orient);
	cylinder->radius = radius;
	return (cylinder);
}
