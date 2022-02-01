/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:24:34 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/01 21:55:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	color_to_int(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

void	draw_pixel(t_img *img, int x, int y, t_color color)
{
	char	*dst;

	dst = img->addr + (y * img->bytes_per_line + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color_to_int(color);
}
