/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:24:34 by lajudy            #+#    #+#             */
/*   Updated: 2022/01/27 23:25:05 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_pixel(t_scene *scene, int x, int y, int color)
{
	char	*dst;

	dst = scene->addr + (y * scene->bytes_per_line + x * (scene->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
