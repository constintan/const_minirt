/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/13 23:06:14 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	hud(t_mlx *mlx)
{
	if (mlx->hud)
	{
//		if (mlx->hud_flash > 50)
//		{
			mlx_string_put(mlx->init, mlx->win, 20, 30, 0xFFFF00, mlx->hud);
//			mlx->hud_flash++;
//			if (mlx->hud_flash > 150)
//				mlx->hud_flash = 0;
//		} else
//			mlx->hud_flash++;
	}
}
