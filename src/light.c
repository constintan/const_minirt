/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 01:31:06 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/02 01:35:22 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_light_back(t_light **lights, t_light *light)
{
	t_light	*l;

	if (!*lights)
		*lights = light;
	else
	{
		l = *lights;
		while (l->next)
			l = l->next;
		l->next = light;
	}
}

void	add_light(t_scene *scene, char *str)
{
	t_vector3	position;
	double		bright;
	t_color		color;

	int			err;

	if (scene->light != NULL)
		ft_error(7);
	err = 0;
	position = new_vector_atof(&str, &err);
	printf("***add_light***\n");
	printf("position.x:%f\n", position.x);
	printf("err:%d\n", err);
	printf("position.y:%f\n", position.y);
	printf("err:%d\n", err);
	printf("position.z:%f\n", position.z);
	printf("err:%d\n", err);
	
	bright = ft_atof(&str, &err);
	printf("bright:%f\n", bright);
	printf("err:%d\n", err);
	check_ratio_limits(bright, &err);
	printf("err:%d\n", err);

	color = new_color_atoc(&str, &err);
	printf("color->r:%d\n", color.r);
	printf("err:%d\n", err);
	printf("color->g:%d\n", color.g);
	printf("err:%d\n", err);
	printf("color->b:%d\n", color.b);
	printf("err:%d\n", err);

	check_endline(&str, &err);
	printf("err:%d\n", err);
	if (err)
		ft_error(7);
//	scene->light = new_light(position, bright, color);
	add_light_back(&scene->light, new_light(position, bright, color));
}

t_light	*new_light(t_vector3 position, double bright, t_color color)
{
	t_light	*light;

	light = kd_calloc(1, sizeof(t_light));
	if (light == NULL)
		ft_error(-1);
	light->position = position;
	light->bright = bright;
	light->color = color;
	return (light);
}
