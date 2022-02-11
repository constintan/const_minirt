/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:12:06 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/11 02:40:06 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rotate_camera_xz(t_camera *camera, int theta)
{
	t_vector2	rotate;
	t_vector3	axis;

	rotate.u = camera->rotate.u - 90;
	rotate.v = 0;
	axis = vector3_rotate_yx(camera->orient, rotate);
	camera->position = matrix3_addition(camera->rotate_origin, vector3_qrotate(matrix3_subtract(camera->position, camera->rotate_origin), theta, axis));
	camera->rotate.v += theta;
}

void	rotate_camera_y(t_camera *camera, int theta)
{
	t_vector3	axis;

	axis = new_vector3(0, 1, 0);
	camera->position = matrix3_addition(camera->rotate_origin, vector3_qrotate(matrix3_subtract(camera->position, camera->rotate_origin), theta, axis));
	camera->rotate.u += theta;
}

static int		rotate_camera(int key, t_scene *scene)
{
	if (key == KEY_UP)
		rotate_camera_xz(scene->camera, 5);
	else if (key == KEY_DOWN)
		rotate_camera_xz(scene->camera, -5);
	else if (key == KEY_LEFT)
		rotate_camera_y(scene->camera, -5);
	else if (key == KEY_RIGHT)
		rotate_camera_y(scene->camera, 5);
	else
		return (0);
	return (1);
}

int		change_fov(int key, t_scene *scene)
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
	return (1);
}

int	key_hook(int key, t_scene *scene)
{
	if (key == KEY_ESC)
		close_minirt();
	else if (key == KEY_R)
	{
		scene->view++;
		if (scene->view >= 7 || scene->view < 0)
			scene->view = 0;
	} else if (key == KEY_ENTER)
		scene->play = TRUE;
	else if (change_fov(key, scene))
		;
	else if (rotate_camera(key, scene))
		;
	else if (key == KEY_W)
		scene->camera->position = matrix3_addition(scene->camera->position, vector3_multiply(vector3_rotate_yx(scene->camera->orient, scene->camera->rotate), 5));
	else if (key == KEY_S)
		scene->camera->position = matrix3_addition(scene->camera->position, vector3_multiply(vector3_rotate_yx(scene->camera->orient, scene->camera->rotate), -5));
	else if (key == KEY_A)
	{
		t_vector2	rotate;
		rotate.u = scene->camera->rotate.u - 90;
		rotate.v = 0;
		scene->camera->position = matrix3_addition(scene->camera->position, vector3_multiply(vector3_rotate_yx(scene->camera->orient, rotate), 5));
	}
	else if (key == KEY_D)
	{
		t_vector2	rotate;
		rotate.u = scene->camera->rotate.u + 90;
		rotate.v = 0;
		scene->camera->position = matrix3_addition(scene->camera->position, vector3_multiply(vector3_rotate_yx(scene->camera->orient, rotate), 5));
	}
	else if (key == KEY_Q)
	{
		t_vector2	rotate;
		rotate.u = scene->camera->rotate.u;
		rotate.v = scene->camera->rotate.v - 90;
		scene->camera->position = matrix3_addition(scene->camera->position, vector3_multiply(vector3_rotate_yx(scene->camera->orient, rotate), 5));
	}
	else if (key == KEY_E)
	{
		t_vector2	rotate;
		rotate.u = scene->camera->rotate.u;
		rotate.v = scene->camera->rotate.v + 90;
		scene->camera->position = matrix3_addition(scene->camera->position, vector3_multiply(vector3_rotate_yx(scene->camera->orient, rotate), 5));
	}
	else if (key == KEY_1)
		scene->maxquality = 1;
	else if (key == KEY_2)
		scene->maxquality = 2;
	else if (key == KEY_3)
		scene->maxquality = 3;
	else if (key == KEY_4)
		scene->maxquality = 4;
	else if (key == KEY_5)
		scene->maxquality = 5;
	else if (key == KEY_6)
		scene->minquality = kd_max(scene->width, scene->height) / 240;
	else if (key == KEY_7)
		scene->minquality = kd_max(scene->width, scene->height) / 120;
	else if (key == KEY_8)
		scene->minquality = kd_max(scene->width, scene->height) / 60;
	else if (key == KEY_9)
		scene->minquality = kd_max(scene->width, scene->height) / 40;
	else if (key == KEY_0)
		scene->minquality = kd_max(scene->width, scene->height) / 20;
	else if (key == KEY_Z)
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
	else if (key == KEY_F)
		reset_camera(scene);
	else if (key == KEY_I)
		scene->light->position.z += 5;
	else if (key == KEY_J)
		scene->light->position.x -= 5;
	else if (key == KEY_K)
		scene->light->position.z -= 5;
	else if (key == KEY_L)
		scene->light->position.x += 5;
	else if (key == KEY_U)
		scene->light->position.y -= 5;
	else if (key == KEY_O)
		scene->light->position.y += 5;
	if (key == KEY_1 || key == KEY_2 || key == KEY_3 || key == KEY_4 || key == KEY_5)
	{
		if (scene->everynframe < scene->maxquality)
			scene->everynframe = scene->maxquality;
		scene->idle = 0;

	}
	else if (key == KEY_U || key == KEY_O || key == KEY_I || key == KEY_J || key == KEY_K || key == KEY_L || key == KEY_Z || key == KEY_X || key == KEY_C || key == KEY_V || key == KEY_B || key == KEY_N || key == KEY_F || key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D || key == KEY_Q || key == KEY_E || key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT || key == KEY_R || key == KEY_OPENBRACKET || key == KEY_CLOSEBRACKET)
	{
		scene->everynframe = scene->minquality;
		scene->rays_set = FALSE;
		scene->idle = 0;
	}
	printf("key %d\n", key);
	return (0);
}
