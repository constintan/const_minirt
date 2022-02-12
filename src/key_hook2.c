/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:12:06 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/12 15:52:25 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	change_fov(int key, t_scene *scene)
{
	if (key == KEY_OPENBRACKET && scene->view)
		scene->camera->fov -= 5;
	else if (key == KEY_OPENBRACKET && !scene->view)
		scene->camera->zoom -= 5;
	else if (key == KEY_CLOSEBRACKET && scene->view)
		scene->camera->fov += 5;
	else if (key == KEY_CLOSEBRACKET && !scene->view)
		scene->camera->zoom += 5;
	else
		return (0);
	redraw_frame(scene);
	return (1);
}

int	change_maxquality(int key, t_scene *scene)
{
	if (key == KEY_1)
		scene->maxquality = 1;
	else if (key == KEY_2)
		scene->maxquality = 2;
	else if (key == KEY_3)
		scene->maxquality = 3;
	else if (key == KEY_4)
		scene->maxquality = 4;
	else if (key == KEY_5)
		scene->maxquality = 5;
	else
		return (0);
	if (scene->everynframe < scene->maxquality)
		scene->everynframe = scene->maxquality;
	scene->idle = 0;
	return (1);
}

int	change_minquality(int key, t_scene *scene)
{
	if (key == KEY_6 && kd_max(scene->width, scene->height) >= 240)
		scene->minquality = kd_max(scene->width, scene->height) / 240;
	else if (key == KEY_7 && kd_max(scene->width, scene->height) >= 120)
		scene->minquality = kd_max(scene->width, scene->height) / 120;
	else if (key == KEY_8 && kd_max(scene->width, scene->height) >= 60)
		scene->minquality = kd_max(scene->width, scene->height) / 60;
	else if (key == KEY_9 && kd_max(scene->width, scene->height) >= 40)
		scene->minquality = kd_max(scene->width, scene->height) / 40;
	else if (key == KEY_0 && kd_max(scene->width, scene->height) >= 20)
		scene->minquality = kd_max(scene->width, scene->height) / 20;
	else if (key == KEY_6 || key == KEY_7 || key == KEY_8 || key == KEY_9
		|| key == KEY_0)
		scene->minquality = 1;
	else
		return (0);
	scene->idle = 0;
	return (1);
}

int	toggle_flags(int key, t_scene *scene)
{
	if (key == KEY_Z)
		toggle(&scene->no_shadows);
	else if (key == KEY_X)
		toggle(&scene->one_light);
	else if (key == KEY_C)
		toggle(&scene->no_lights);
	else if (key == KEY_V)
		toggle(&scene->no_specular);
	else if (key == KEY_B)
		toggle(&scene->checkerboard);
	else if (key == KEY_N)
		toggle(&scene->bump);
	else if (key == KEY_M)
		toggle(&scene->gamma_correction);
	else
		return (0);
	if (key == KEY_M)
		scene->idle = 0;
	else
		redraw_frame(scene);
	return (1);
}

int	move_light(int key, t_scene *scene)
{
	if (!scene->light)
		return (0);
	if (key == KEY_SPACE)
	{
		scene->current_light = scene->current_light->next;
		if (!scene->current_light)
			scene->current_light = scene->light;
	}
	else if (key == KEY_I)
		scene->current_light->position.z += 5;
	else if (key == KEY_J)
		scene->current_light->position.x -= 5;
	else if (key == KEY_K)
		scene->current_light->position.z -= 5;
	else if (key == KEY_L)
		scene->current_light->position.x += 5;
	else if (key == KEY_U)
		scene->current_light->position.y -= 5;
	else if (key == KEY_O)
		scene->current_light->position.y += 5;
	else
		return (0);
	if (!(key == KEY_SPACE && !scene->one_light))
		redraw_frame(scene);
	return (1);
}
