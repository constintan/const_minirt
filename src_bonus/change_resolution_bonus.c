/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/13 23:06:14 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	change_resolution(int key, t_mlx *mlx)
{
	if (key == KEY_1 && mlx->width != 640)
	{
		mlx->width = 640;
		mlx->height = 480;
	}
	else if (key == KEY_2 && mlx->width != 800)
	{
		mlx->width = 800;
		mlx->height = 600;
	}
	else if (key == KEY_3 && mlx->width != 1280)
	{
		mlx->width = 1280;
		mlx->height = 720;
	}
	else if (key == KEY_4 && mlx->width != 1920)
	{
		mlx->width = 1920;
		mlx->height = 1080;
	}
	restart_window(mlx);
}
