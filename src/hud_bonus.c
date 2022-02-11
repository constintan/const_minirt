/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/11 22:17:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minirt_bonus.h"

void	hud(t_scene *scene)
{
	t_bonus	*bonus;

	bonus = scene->bonus;
	kd_free(scene->hud);
	if (!scene->view)
		scene->hud = kd_strf("quality %d/%d view %d zoom %d frame %dms", scene->everynframe, scene->minquality, scene->view, (int)scene->camera->zoom, (int)mtv() - (int)bonus->timestamp);
	else
		scene->hud = kd_strf("quality %d/%d view %d fov %d frame %dms", scene->everynframe, scene->minquality, scene->view, (int)scene->camera->fov, (int)mtv() - (int)bonus->timestamp);
	mlx_string_put(scene->mlx, scene->window, 20, 30, 0xFFFF00, scene->hud);
}
