/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/12 04:01:47 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	hud(t_scene *scene)
{
	kd_free(scene->hud);
	scene->hud = kd_strjoin_free("quality ", kd_itoa(scene->everynframe), 2);
	scene->hud = kd_strjoin_free(scene->hud, "/", 1);
	scene->hud = kd_strjoin_free(scene->hud, kd_itoa(scene->minquality), 0);
	scene->hud = kd_strjoin_free(scene->hud, " view ", 1);
	scene->hud = kd_strjoin_free(scene->hud, kd_itoa(scene->view), 0);
	if (!scene->view)
	{
		scene->hud = kd_strjoin_free(scene->hud, " zoom ", 1);
		scene->hud = kd_strjoin_free(scene->hud,
				kd_itoa((int)scene->camera->zoom), 0);
	}
	else
	{
		scene->hud = kd_strjoin_free(scene->hud, " fov ", 1);
		scene->hud = kd_strjoin_free(scene->hud,
				kd_itoa((int)scene->camera->fov), 0);
	}
	mlx_string_put(scene->mlx, scene->window, 20, 30, 0xFFFF00, scene->hud);
}
