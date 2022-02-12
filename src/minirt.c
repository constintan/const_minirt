/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:43:53 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/12 01:04:03 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	vars_init(t_scene *scene)
{
	scene->view = 5;
	scene->gamma = 1;
	scene->maxquality = 1;
	scene->minquality = kd_max(scene->width, scene->height) / 20;
	scene->everynframe = scene->minquality;
	scene->bumpmap = new_image("sprites/plane_bump_map.xpm", scene);
	scene->texturemap = new_image("sprites/textureground.xpm", scene);
	scene->rays = kd_calloc(scene->width * scene->height, sizeof(t_ray));
}

int	main(int argc, char **argv)
{
	t_scene *scene;

	if (argc == 1 || invalid_filename(argv[1]))
		ft_error(1);
	scene = (t_scene *)kd_calloc(1, sizeof(t_scene));
	if (scene == NULL)
		ft_error(-1);
	scene->maps = &argv[1];
	scene_init(*scene->maps, scene);
	mlx_window_init(scene);
	vars_init(scene);
	mlx_loop_hook(scene->mlx, render_next_frame, scene);
	mlx_hook(scene->window, 2, (1L << 0), key_hook, scene);
	mlx_hook(scene->window, 17, 0, close_minirt, scene);
	mlx_mouse_hook(scene->window, mouse_hook, scene);
	mlx_loop(scene->mlx);
}
