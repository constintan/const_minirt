/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:43:53 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/05 01:31:00 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_minirt(void)
{
	kd_free_all();
	printf("\nExit\n");
	exit(0);
}

void	reset_game(t_scene *scene)
{
	(void)scene;
}

static int	key_hook(int key, t_scene *scene)
{
	if (key == KEY_ESC)
		close_minirt();
	else if (key == KEY_R)
	{
		scene->view++;
		if (scene->view >= 6 || scene->view < 0)
			scene->view = 0;
//		reset_game(mlx);
	} else if (key == KEY_ENTER || key == KEY_TAB)
		scene->play = TRUE;
//		next_level(mlx);
//	if (check_move(key, mlx) && scene->hud)
//		scene->hud = kd_free(scene->hud);
	else if (key == KEY_OPENBRACKET && scene->view)
		scene->camera->fov -= 5;
	else if (key == KEY_OPENBRACKET && !scene->view)
		scene->camera->zoom -= 5;
	else if (key == KEY_CLOSEBRACKET && scene->view)
		scene->camera->fov += 5;
	else if (key == KEY_CLOSEBRACKET && !scene->view)
		scene->camera->zoom += 5;
	printf("key %d\n", key);
	return (0);
}

// static int	mouse_hook(int button, int x, int y, t_mlx *mlx)
// {
// t_vector3		proportion;
// t_vector3	direction;

// proportion.x = (x - mlx->win_w / (double)2) / mlx->win_w * (double)2;
// proportion.y = (y - mlx->win_h / (double)2) / mlx->win_w * (double)2;
// proportion.z = 1;
// direction = vector3_normalise(proportion);
// printf("x %d, proportion.x %f, y %d, proportion.y %f\n", x, proportion.x, y, proportion.y);
// printf("direction.x %f, direction.y %f, direction.z %f\n", direction.x, direction.y, direction.z);
// (void)button;
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_scene *scene;

	if (argc == 1 || invalid_filename(argv[1]))
		ft_error(1);
	scene = scene_init(argv[1]);
	while (--argc > 1)
	{
		if (argv[argc][0] == '-' && kd_strchr(argv[argc], 's'))
			scene->no_shadows = TRUE;
		if (argv[argc][0] == '-' && kd_strchr(argv[argc], 'l'))
			scene->one_light = TRUE;
		if (argv[argc][0] == '-' && kd_strchr(argv[argc], 'L'))
			scene->no_lights = TRUE;
	}
	scene->hud = kd_strf("%s", "Press AWSD to move");
	scene->view = 1;
	mlx_loop_hook(scene->mlx, render_next_frame, scene);
	mlx_hook(scene->window, 2, (1L << 0), key_hook, scene);
	mlx_hook(scene->window, 17, 0, close_minirt, scene);
	// mlx_mouse_hook(scene->window, mouse_hook, scene);
	mlx_loop(scene->mlx);
}
