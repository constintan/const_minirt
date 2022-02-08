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

// color = new_color_atof(ft_atoc(&str, &err), ft_atoc(&str, &err), ft_atoc(&str, &err));
t_color	new_color_atoc(char **str, int *err)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoc(str, err);
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '\0')
	{
		printf("Color not specified. Init with white color\n");
		return (new_color(255, 255, 255));
	}
	if (**str == ',')
		(*str)++;
	g = ft_atoc(str, err);
	while (ft_isspace(**str))
		(*str)++;
	if (**str == ',')
		(*str)++;
	b = ft_atoc(str, err);

	return (colour_clamp(new_color(r, g, b)));
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

t_color	colour_amplify(t_color colour, double amplifier)
{
	colour.r *= amplifier;
	colour.g *= amplifier;
	colour.b *= amplifier;
	return (colour);
}

t_color	colour_add(t_color colour, t_color colour_add)
{
	colour.r += colour_add.r;
	colour.g += colour_add.g;
	colour.b += colour_add.b;
	return (colour);
}

t_color	colour_matrix_amplify(t_color colour, t_color colour_amplifier)
{
	int	mix;

	mix = 10;
	colour.r = colour.r * colour_amplifier.r / 255
			   + colour_amplifier.g / mix + colour_amplifier.b / mix;
	colour.g = colour.g * colour_amplifier.g / 255
			   + colour_amplifier.r / mix + colour_amplifier.b / mix;
	colour.b = colour.b * colour_amplifier.b / 255
			   + colour_amplifier.r / mix + colour_amplifier.g / mix;
	return (colour);
}
