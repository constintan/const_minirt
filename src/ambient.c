/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 01:12:30 by lajudy            #+#    #+#             */
/*   Updated: 2022/01/29 01:35:16 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_ratio_limits(double bright, int *err)
{
	if (bright < 0 || bright > 1)
		*err = 1;
}

void	add_ambient(t_scene *scene, char *str)
{
	double	bright;
	t_color	color;
	int		err;

	if (scene->ambient != NULL)
		ft_error(6);
	err = 0;
	bright = ft_atof(&str, &err);
	check_ratio_limits(bright, &err);
	color = new_color_atoc(&str, &err);
	check_endline(&str, &err);
	if (err)
		ft_error(6);
	scene->ambient = new_ambient(bright, color);
}

t_ambient	*new_ambient(double bright, t_color color)
{
	t_ambient	*ambient;

	ambient = kd_calloc(1, sizeof(t_ambient));
	if (ambient == NULL)
		ft_error(-1);
	ambient->bright = bright;
	ambient->color = color;
	return (ambient);
}
