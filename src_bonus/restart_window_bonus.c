/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/01/27 18:17:28 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	restart_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->init, mlx->win);
	mlx_destroy_image(mlx->init, mlx->sim->ptr);
	mlx->sim = kd_free(mlx->sim);
	create_window(mlx);
}
