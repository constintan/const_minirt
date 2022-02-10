/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: konstanting <konstanting@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:19:30 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/05 01:50:04 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	*new_scene(void)
{
	t_scene	*scene;

	scene = (t_scene *)kd_calloc(1, sizeof(t_scene));
	if (scene == NULL)
		ft_error(-1);
	scene->width = WINDOW_WIDTH;
	scene->height = WINDOW_HEIGHT;
	scene->mlx = mlx_init();
	if (scene->mlx == NULL)
		ft_error(-1);
	scene->window = mlx_new_window(scene->mlx, scene->width, scene->height, WN);
	if (scene->window == NULL)
		ft_error(-1);
	scene->img = kd_calloc(1, sizeof(t_img));
	if (scene->img == NULL)
		ft_error(-1);
	scene->img->img = mlx_new_image(scene->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (scene->img->img == NULL)
		ft_error(-1);
	scene->img->addr = mlx_get_data_addr(scene->img->img,
			&scene->img->bits_per_pixel,
			&scene->img->bytes_per_line, &scene->img->endian);
	if (scene->img->addr == NULL)
		ft_error(-1);
	scene->img2 = kd_calloc(1, sizeof(t_img));
	if (scene->img2 == NULL)
		ft_error(-1);
	scene->img2->img = mlx_new_image(scene->mlx, scene->width, scene->height);
	if (scene->img2->img == NULL)
		ft_error(-1);
	scene->img2->addr = mlx_get_data_addr(scene->img2->img,
			&scene->img2->bits_per_pixel,
			&scene->img2->bytes_per_line, &scene->img2->endian);
	if (scene->img2->addr == NULL)
		ft_error(-1);
	return (scene);
}
// sp 0,0,20.6 12.6 10,0,255

void	parse_line(t_scene *scene, char *str)
{
	while (ft_isspace(*str))
		str++;
	if (str[0] == '\0' || str[0] == '#' || (str[0] == '/' && str[1] == '/'))
		;
	else if (str[0] == 's' && str[1] == 'p')
		add_sphere(scene, &str[2]);
	else if (str[0] == 'p' && str[1] == 'l')
		add_plane(scene, &str[2]);
	else if (str[0] == 'c' && str[1] == 'y')
		add_cylinder(scene, &str[2]);
	else if (str[0] == 'c' && str[1] == 'n')
		add_cone(scene, &str[2]);
	else if (str[0] == 'C')
		add_camera(scene, &str[1]);
	else if (str[0] == 'A')
		add_ambient(scene, &str[1]);
	else if (str[0] == 'L')
		add_light(scene, &str[1]);
	else
		ft_error(5);
}

t_scene	*scene_init(char *filename)
{
	t_scene	*scene;
	char	*str;
	int		fd;

	scene = new_scene();
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error(2);
	str = get_next_line(fd);
	while (str)
	{
		parse_line(scene, str);
		free(str);
		str = get_next_line(fd);
	}
	return (scene);
}
