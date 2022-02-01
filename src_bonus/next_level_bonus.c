/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_level.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/01/30 20:10:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	next_level(t_mlx *mlx)
{
	//clean some vars
	if (!mlx->maps[++mlx->map_index])
	{
		kd_printf("This was the last map... Starting over!\n");
		mlx->map_index = 0;
	}
	//parse new map like: parse_map(mlx->maps[mlx->map_index], mlx);
	//inits
	//prepares
	//resets
	kd_printf("Playing: %s\n", mlx->maps[mlx->map_index]);
}
