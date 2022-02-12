/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 23:22:20 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/11 14:25:32 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_color	colour_gamma_collect(t_color colour, t_scene *scene)
{
	scene->gamma = fmax(scene->gamma,
			kd_max(kd_max(colour.r, colour.g), colour.b) / (double)255);
	return (colour);
}

t_color	colour_gamma_apply(t_color colour, t_scene *scene)
{
	if (scene->gamma_correction)
	{
		colour.r /= scene->gamma;
		colour.g /= scene->gamma;
		colour.b /= scene->gamma;
		return (colour);
	}
	else
		return (colour_clamp(colour));
}
