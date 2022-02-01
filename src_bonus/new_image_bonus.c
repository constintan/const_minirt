/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/13 23:06:14 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_img	*new_image(t_mlx *mlx, int w, int h)
{
	t_img	*img;

	img = kd_malloc(sizeof(t_img)); //check for null?
	img->ptr = kd_nn(mlx_new_image(mlx->init, w, h),
			"Error\nmlx_new_image() is null");
	img->addr = kd_nn(mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
				&img->line_length, &img->endian),
			"Error\nmlx_get_data_addr() is null");
	return (img);
}
