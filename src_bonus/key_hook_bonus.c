/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/01 10:53:22 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_bool	check_move(int key, t_mlx *mlx)
{
	t_bool	moved;
	t_obj	*obj;
	double	x;
	double	y;

	obj = mlx->obj;
	while (obj && obj->type != SPHERE)
		obj = obj->next;
	moved = move(mlx);
	if (key == KEY_W)
	{
//		obj->position.y += 5;
//		mlx->light->position.y += 5;
//		mlx->camera->orientation = vector3_rotate(mlx->camera->orientation, 0, 5);
		mlx->camera->position.y += 5;
//		mlx->camera->rotate.v += 5;
		moved = TRUE;
	}
	else if (key == KEY_S)
	{
//		obj->position.y -= 5;
//		mlx->light->position.y -= 5;
//		mlx->camera->orientation = vector3_rotate(mlx->camera->orientation, 0, -5);
		mlx->camera->position.y -= 5;
//		mlx->camera->rotate.v -= 5;
		moved = TRUE;
	}
	else if (key == KEY_A)
	{
//		obj->position.x -= 5;
//		mlx->light->position.x -= 5;
//		mlx->camera->orientation = vector3_rotate(mlx->camera->orientation, -5, 0);
		mlx->camera->position.x -= 5;
//		mlx->camera->rotate.u -= 5;
		moved = TRUE;
	}
	else if (key == KEY_D)
	{
//		obj->position.x += 5;
//		mlx->light->position.x += 5;
//		mlx->camera->orientation = vector3_rotate(mlx->camera->orientation, 5, 0);
		mlx->camera->position.x += 5;
//		mlx->camera->rotate.u += 5;
		moved = TRUE;
	}
	else if (key == KEY_UP)
		mlx->light->position.y += 5;
	else if (key == KEY_DOWN)
		mlx->light->position.y -= 5;
	else if (key == KEY_LEFT)
		mlx->light->position.x -= 5;
	else if (key == KEY_RIGHT)
		mlx->light->position.x += 5;
	else if (key == KEY_1 || key == KEY_2 || key == KEY_3 || key == KEY_4)
		change_resolution(key, mlx);
	x = mlx->camera->rotate.u;
	y = mlx->camera->rotate.v;
	if (y > 90 && y < 270)
	{
		x += 180;
		y = 270 - fmod(y, 270);
	}
	if (y < -90 && y > -270)
	{
		x -= 180;
		y = 270 + fmod(y, 270);
	}
	printf("3 %f, %f, %f; %f %f\n", 180 / M_PI * vector3_rotate(mlx->camera->orient, mlx->camera->rotate).x, 180 / M_PI * vector3_rotate(mlx->camera->orient, mlx->camera->rotate).y, 180 / M_PI * vector3_rotate(mlx->camera->orient, mlx->camera->rotate).z, mlx->camera->rotate.u, mlx->camera->rotate.v);
	printf("%f %f\n", x, y);
	return (moved);
}

int	key_hook(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		close_game();
	else if (key == KEY_R)
	{
		mlx->view++;
		if (mlx->view >= 3 || mlx->view < 0)
			mlx->view = 0;
//		reset_game(mlx);
	}
	else if (key == KEY_ENTER || key == KEY_TAB)
		mlx->play = TRUE;
//		next_level(mlx);
	if (check_move(key, mlx) && mlx->hud)
		mlx->hud = kd_free(mlx->hud);
	return (0);
}
