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

// float	get_sp_radius(char **str)
// {
// 	float	res;

// 	res = ft_atof(*str);
// }

// sp 0,0,20.6 12.6 10,0,255
//return -1 in case of invalid data

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

	// return (1);
}

t_cylinder		*new_cylinder(t_vector3 position, t_vector3 orient, double radius, double height, t_color color)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		ft_error(-1);
	cylinder->position = position;
	cylinder->orient = orient;
	cylinder->radius = radius;
	cylinder->height = height;
	cylinder->color = color;
	cylinder->next = NULL;
	return (cylinder);
}
