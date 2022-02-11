/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:12:06 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/11 16:29:49 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	redraw_frame(t_scene *scene)
{
	scene->everynframe = scene->minquality;
	scene->rays_set = FALSE;
	scene->idle = 0;
	scene->gamma = 1;
}

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

int		rotate_camera(int key, t_scene *scene)
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
	redraw_frame(scene);
	return (1);
}

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

static void	move_camera_x(t_camera *camera, double distance)
{
	t_vector2	rotate;

	rotate.u = camera->rotate.u + 90;
	rotate.v = 0;
	camera->position = matrix3_addition(camera->position, vector3_multiply(vector3_rotate_yx(camera->orient, rotate), distance));
}

static void	move_camera_y(t_camera *camera, double distance)
{
	t_vector2	rotate;

	rotate.u = camera->rotate.u;
	rotate.v = camera->rotate.v + 90;
	camera->position = matrix3_addition(camera->position, vector3_multiply(vector3_rotate_yx(camera->orient, rotate), distance));
}

static void	move_camera_z(t_camera *camera, double distance)
{
	t_vector2	rotate;

	rotate = camera->rotate;
	camera->position = matrix3_addition(camera->position, vector3_multiply(vector3_rotate_yx(camera->orient, rotate), distance));
}

int	move_camera(int key, t_scene *scene)
{
	if (key == KEY_W)
		move_camera_z(scene->camera, 5);
	else if (key == KEY_S)
		move_camera_z(scene->camera, -5);
	else if (key == KEY_A)
		move_camera_x(scene->camera, -5);
	else if (key == KEY_D)
		move_camera_x(scene->camera, 5);
	else if (key == KEY_Q)
		move_camera_y(scene->camera, -5);
	else if (key == KEY_E)
		move_camera_y(scene->camera, 5);
	else
		return (0);
	scene->camera->rotate_origin = scene->camera->position;
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
	if (key == KEY_6)
		scene->minquality = kd_max(scene->width, scene->height) / 240;
	else if (key == KEY_7)
		scene->minquality = kd_max(scene->width, scene->height) / 120;
	else if (key == KEY_8)
		scene->minquality = kd_max(scene->width, scene->height) / 60;
	else if (key == KEY_9)
		scene->minquality = kd_max(scene->width, scene->height) / 40;
	else if (key == KEY_0)
		scene->minquality = kd_max(scene->width, scene->height) / 20;
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
	if (key != KEY_SPACE)
		redraw_frame(scene);
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
		redraw_frame(scene);
	} else if (key == KEY_ENTER)
		scene->play = TRUE;
	else if (key == KEY_F)
		reset_camera(scene);
	else if (change_fov(key, scene) || rotate_camera(key, scene)
	|| move_camera(key, scene) || change_maxquality(key, scene)
	|| change_minquality(key, scene) || toggle_flags(key, scene)
	|| move_light(key, scene))
		;
//	printf("key %d\n", key);
	return (0);
}
