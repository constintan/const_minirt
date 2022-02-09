/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:30:30 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/01 22:19:55 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_plane(t_scene *scene, char *str)
{
	t_plane		*plane;
	t_vector3	position;
	t_vector3	orient;
	t_color		color;
	int			err;

	err = 0;
	position = new_vector_atof(&str, &err);
	orient = new_vector_atof(&str, &err);
	check_direction_limits(orient, &err);
	color = new_color_atoc(&str, &err);
	check_endline(&str, &err);
	if (err)
		ft_error(8);
	plane = new_plane(position, orient, color);
	plane->next = scene->planes;
	scene->planes = plane;
}

t_plane	*new_plane(t_vector3 position, t_vector3 orient, t_color color)
{
	t_plane	*plane;

	plane = kd_calloc(1, sizeof(t_plane));
	if (plane == NULL)
		ft_error(-1);
	plane->position = position;
	plane->orient = vector3_normalise(orient);
	plane->color = color;
	return (plane);
}
