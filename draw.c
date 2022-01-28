/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:24:34 by lajudy            #+#    #+#             */
/*   Updated: 2022/01/29 00:26:44 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	color_to_int(t_color *color)
{
	int	result;

	result = color->r;
	result = result << 8;
	result += color->g;
	result = result << 8;
	result += color->b;
	return (result);
}

void	draw_pixel(t_scene *scene, int x, int y, t_color *color)
{
	char	*dst;


	dst = scene->addr + (y * scene->bytes_per_line + x * (scene->bits_per_pixel / 8));
	*(unsigned int *)dst = color_to_int(color);
	// dst = scene->addr + (y * scene->bytes_per_line + x * (scene->bits_per_pixel / 8));
	// *(unsigned int *)dst = 10;
	// (void)color;
}
