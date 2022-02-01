/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/01 09:15:17 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

unsigned int	colour_rgb2hex(t_color colour)
{
	return (colour.r << 16 | colour.g << 8 | colour.b);
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
	return (colour_clamp(colour));
}

t_color	colour_add(t_color colour, t_color colour_add)
{
	colour.r += colour_add.r;
	colour.g += colour_add.g;
	colour.b += colour_add.b;
	return (colour_clamp(colour));
}

t_color	colour_matrix_amplify(t_color colour, t_color colour_amplifier)
{
	colour.r = colour.r * colour_amplifier.r / 255
			   + colour_amplifier.g / 10 + colour_amplifier.b / 10;
	colour.g = colour.g * colour_amplifier.g / 255
			   + colour_amplifier.r / 10 + colour_amplifier.b / 10;
	colour.b = colour.b * colour_amplifier.b / 255
			   + colour_amplifier.r / 10 + colour_amplifier.g / 10;
	return (colour);
}

