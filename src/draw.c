/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:24:34 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/06 11:43:52 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	color_to_int(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

void	draw_pixel(t_scene *scene, int x, int y, t_color color)
{
	char	*dst;
	t_img	*img;
	int		i;
	int		j;

	if (!scene->oddframe)
		img = scene->img;
	else
		img = scene->img2;
	x *= scene->everynframe;
	y *= scene->everynframe;
	i = 0;
	while (i < scene->everynframe && y + i < scene->win_h)
	{
		j = 0;
		while (j < scene->everynframe && x + j < scene->win_w)
		{
			dst = img->addr + ((y + i) * img->bytes_per_line + (x + j) * (img->bits_per_pixel / 8));
			*(unsigned int *)dst = color_to_int(color);
			j++;
		}
		i++;
	}
}
