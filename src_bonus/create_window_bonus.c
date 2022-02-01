/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: konstanting <konstanting@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/01 23:11:44 by konstanting      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	reset_game(t_mlx *mlx)
{
	(void)mlx;
}

// static int	mouse_hook(int button, int x, int y, t_mlx *mlx)
// {
	// t_vector3		proportion;
	// t_vector3	direction;

	// proportion.x = (x - mlx->win_w / (double)2) / mlx->win_w * (double)2;
	// proportion.y = (y - mlx->win_h / (double)2) / mlx->win_w * (double)2;
	// proportion.z = 1;
	// direction = vector3_normalise(proportion);
	// printf("x %d, proportion.x %f, y %d, proportion.y %f\n", x, proportion.x, y, proportion.y);
	// printf("direction.x %f, direction.y %f, direction.z %f\n", direction.x, direction.y, direction.z);
	// (void)button;
// 	return (0);
// }

void	create_window(t_mlx *mlx)
{
	// mlx->win = kd_nn(mlx_new_window(mlx->init, mlx->win_w, mlx->win_h,
	// 			"minirt"), "Error\nmlx_new_window() is null\n");
	// mlx->sim = new_image(mlx, mlx->win_w, mlx->win_h);
	scene->hud = kd_strf("%s", "Press AWSD to move");
	mlx_loop_hook(scene->mlx, render_next_frame, scene);
	mlx_hook(scene->window, 2, (1L << 0), key_hook, scene);
	mlx_hook(scene->window, 17, 0, close_game, scene);
	// mlx_mouse_hook(scene->window, mouse_hook, scene);
	mlx_loop(scene->mlx);
}
