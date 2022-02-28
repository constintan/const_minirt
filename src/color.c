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
	if ((**str == '\0' || kd_isalpha(**str)) && BONUS )
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

t_color	colour_clamp(t_color colour)
{
	if (colour.r < 0)
		colour.r = 0;
	else if (colour.r > 255)
		colour.r = 255;
	if (colour.g < 0)
		colour.g = 0;
	else if (colour.g > 255)
		colour.g = 255;
	if (colour.b < 0)
		colour.b = 0;
	else if (colour.b > 255)
		colour.b = 255;
	return (colour);
}
