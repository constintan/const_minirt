/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: konstanting <konstanting@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:19:30 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/12 00:26:17 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	mlx_window_init(t_scene *scene)
{
	if (WINDOW_WIDTH == 0)
		WINDOW_WIDTH = WINDOW_WIDTH_DEFAULT;
	if (WINDOW_HEIGHT == 0)
		WINDOW_HEIGHT = WINDOW_HEIGHT_DEFAULT;
	scene->width = WINDOW_WIDTH;
	scene->height = WINDOW_HEIGHT;
	scene->mlx = mlx_init();
	if (scene->mlx == NULL)
		ft_error(-1);
	scene->window = mlx_new_window(scene->mlx, scene->width, scene->height, WN);
	if (scene->window == NULL)
		ft_error(-1);
	scene->img = new_image(NULL, WINDOW_WIDTH, WINDOW_HEIGHT, scene);
	scene->img2 = new_image(NULL, WINDOW_WIDTH, WINDOW_HEIGHT, scene);
}
// sp 0,0,20.6 12.6 10,0,255

void	parse_line(t_scene *scene, char *str)
{
	while (ft_isspace(*str))
		str++;
	if (str[0] == '\0' || (BONUS && (str[0] == '#' || check_identyfier(str, "//"))))
		;
	else if (check_identyfier(str, "sp"))
		add_sphere(scene, &str[2]);
	else if (check_identyfier(str, "pl"))
		add_plane(scene, &str[2]);
	else if (check_identyfier(str, "cy"))
		add_cylinder(scene, &str[2]);
	else if (check_identyfier(str, "cn") || check_identyfier(str, "co"))
		add_cone(scene, &str[2]);
	else if (check_identyfier(str, "c"))
		add_camera(scene, &str[1]);
	else if (check_identyfier(str, "a"))
		add_ambient(scene, &str[1]);
	else if (check_identyfier(str, "l"))
		add_light(scene, &str[1]);
	else if (check_identyfier(str, "r"))
		init_resolution(scene, &str[1]);
	else if (check_identyfier(str, "sq") || check_identyfier(str, "tr")
			|| check_identyfier(str, "aa")
			|| check_identyfier(str, "sky") || check_identyfier(str, "cb"))
		;
	else
		ft_error(5);
}

void	scene_init(char *filename, t_scene *scene)
{
	char	*str;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error(2);
	str = kd_malloc_add(get_next_line(fd));
	WINDOW_WIDTH = 0;
	WINDOW_HEIGHT = 0;
	while (str)
	{
		parse_line(scene, str);
		kd_free(str);
		str = kd_malloc_add(get_next_line(fd));
	}
	if (scene->camera == NULL)
		scene->camera = new_camera(new_vector3(0, 0, 0),
				new_vector3(0, 0, 1), 70);
	close(fd);
}
