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

#include "minirt.h"

void	hud(t_scene *scene)
{
	if (scene->hud)
	{
//		if (mlx->hud_flash > 50)
//		{
			mlx_string_put(scene->mlx, scene->window, 20, 30, 0xFFFF00, scene->hud);
//			mlx->hud_flash++;
//			if (mlx->hud_flash > 150)
//				mlx->hud_flash = 0;
//		} else
//			mlx->hud_flash++;
	}
}
