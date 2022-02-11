/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:43:53 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/11 11:59:42 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


static t_img	*new_image(char *path, t_scene *scene)
{
	t_img	*img;

	img = kd_calloc(1, sizeof(t_img));
	if (!img)
		ft_error(-1);
	img->img = mlx_xpm_file_to_image(scene->mlx, path, &img->width, &img->height);
	if (!img->img)
		ft_error(-1);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->bytes_per_line, &img->endian);
	if (!img->addr)
		ft_error(-1);
	return (img);
}

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
	scene->view = 5;
//	scene->bumpmap = new_image("sprites/kubiki.xpm", scene);
//	scene->bumpmap = new_image("sprites/normal_map4.xpm", scene);
	scene->bumpmap = new_image("sprites/plane_bump_map.xpm", scene);
	scene->texturemap = new_image("sprites/textureground.xpm", scene);
	printf("bonus = %d\n", BONUS);
	scene->maxquality = 1;
	scene->gamma = 1;
	scene->minquality = kd_max(scene->width, scene->height) / 20;
	scene->everynframe = scene->minquality;
	scene->rays = kd_calloc(scene->width * scene->height, sizeof(t_ray));
	mlx_loop_hook(scene->mlx, render_next_frame, scene);
	mlx_hook(scene->window, 2, (1L << 0), key_hook, scene);
	mlx_hook(scene->window, 17, 0, close_minirt, scene);
	mlx_mouse_hook(scene->window, mouse_hook, scene);
	mlx_loop(scene->mlx);
}
