/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 23:22:20 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/08 11:06:18 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	new_color(int r, int g, int b)
{
	t_color	result;

	result.r = r;
	result.g = g;
	result.b = b;
	return (colour_clamp(result));
}

t_color	new_light_color_atoc(char **str, int *err)
{
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '\0')
	{
		ft_putstr_fd("Light color not specified. Init with white color\n", 1);
		return (new_color(255, 255, 255));
	}
	if (!BONUS)
		ft_error(10);
	return (new_color_atoc(str, err));
}

t_color	new_color_atoc(char **str, int *err)
{
	int	r;
	int	g;
	int	b;

	while (ft_isspace(**str))
		(*str)++;
	if (**str == ',')
		(*str)++;
	if (**str == '\0' && BONUS)
	{
		ft_putstr_fd("Color not specified. Init with white color\n", 1);
		return (new_color(255, 255, 255));
	}
	r = ft_atoc(str, err);
	if (**str == ',')
		(*str)++;
	g = ft_atoc(str, err);
	if (**str == ',')
		(*str)++;
	b = ft_atoc(str, err);
	return (new_color(r, g, b));
}
