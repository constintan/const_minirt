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

void	hud(t_scene *scene)
{
	kd_free(scene->hud);
	if (!scene->view)
		scene->hud = kd_strf("quality %d/%d view %d zoom %d", scene->everynframe, scene->minquality, scene->view, (int)scene->camera->zoom);
	else
		scene->hud = kd_strf("quality %d/%d view %d fov %d", scene->everynframe, scene->minquality, scene->view, (int)scene->camera->fov);
	mlx_string_put(scene->mlx, scene->window, 20, 30, 0xFFFF00, scene->hud);

}
