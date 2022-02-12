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
	camera->position = matrix3_addition(camera->rotate_origin, vector3_qrotate(
				matrix3_subtract(camera->position, camera->rotate_origin),
				theta, axis));
	camera->rotate.v += theta;
}

void	rotate_camera_y(t_camera *camera, int theta)
{
	t_vector3	axis;

	axis = new_vector3(0, 1, 0);
	camera->position = matrix3_addition(camera->rotate_origin, vector3_qrotate(
				matrix3_subtract(camera->position, camera->rotate_origin),
				theta, axis));
	camera->rotate.u += theta;
}

int	rotate_camera(int key, t_scene *scene)
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

//	printf("key %d\n", key);
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
	}
	else if (key == KEY_ENTER)
		scene->play++;
	else if (key == KEY_F)
		reset_camera(scene);
	else if (key == KEY_TAB)
		next_scene(scene);
	else if (change_fov(key, scene) || rotate_camera(key, scene)
		|| move_camera(key, scene) || change_maxquality(key, scene)
		|| change_minquality(key, scene) || toggle_flags(key, scene)
		|| move_light(key, scene))
		;
	return (0);
}
