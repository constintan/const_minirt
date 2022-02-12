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

static void	move_camera_y(t_camera *camera, double distance)
{
	t_vector2	rotate;

	rotate.u = camera->rotate.u;
	rotate.v = camera->rotate.v + 90;
	camera->position = matrix3_addition(camera->position,
			vector3_multiply(vector3_rotate_yx(camera->orient, rotate),
				distance));
}

static void	move_camera_x(t_camera *camera, double distance)
{
	t_vector2	rotate;

	rotate.u = camera->rotate.u + 90;
	rotate.v = 0;
	camera->position = matrix3_addition(camera->position,
			vector3_multiply(vector3_rotate_yx(camera->orient, rotate),
				distance));
}

static void	move_camera_z(t_camera *camera, double distance)
{
	t_vector2	rotate;

	rotate = camera->rotate;
	camera->position = matrix3_addition(camera->position,
			vector3_multiply(vector3_rotate_yx(camera->orient, rotate),
				distance));
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
