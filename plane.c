/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: konstanting <konstanting@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:30:30 by lajudy            #+#    #+#             */
/*   Updated: 2022/01/31 23:36:44 by konstanting      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// float	get_sp_radius(char **str)
// {
// 	float	res;

// 	res = ft_atof(*str);
// }

// sp 0,0,20.6 12.6 10,0,255
//return -1 in case of invalid data
void	add_plane(t_scene *scene, char *str)
{
	t_plane	*plane;
	t_vector	*position;
	t_vector	*orient;
	t_color		*color;
	int			err;

	err = 0;
	position = new_vector_atof(&str, &err);
	printf("***add_plane***\n");
	printf("position->x:%f\n", position->x);
	printf("err:%d\n", err);
	printf("position->y:%f\n", position->y);
	printf("err:%d\n", err);
	printf("position->z:%f\n", position->z);
	printf("err:%d\n", err);
	// center = new_vector(3, 2, -32.8);

	orient = new_vector_atof(&str, &err);
	printf("orient->x:%f\n", orient->x);
	printf("err:%d\n", err);
	printf("orient->y:%f\n", orient->y);
	printf("err:%d\n", err);
	printf("orient->z:%f\n", orient->z);
	printf("err:%d\n", err);

	check_direction_limits(orient, &err);
	printf("err:%d\n", err);

	color = new_color_atoc(&str, &err);
	printf("color->r:%d\n", color->r);
	printf("color->g:%d\n", color->g);
	printf("color->b:%d\n", color->b);

	printf("err:%d\n", err);
	check_endline(&str, &err);
	printf("err:%d\n", err);
	if (err)
		ft_error(8);
	plane = new_plane(position, orient, color);
	plane->next = scene->planes;
	scene->planes = plane;

	// return (1);
}

t_plane			*new_plane(t_vector *position, t_vector *orient, t_color *color)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (plane == NULL)
		ft_error(-1);
	plane->position = position;
	plane->orient = orient;
	plane->color = color;
	plane->next = NULL;
	return (plane);
}
