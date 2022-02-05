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
	// scene->camera = NULL;
	// scene->ambient = NULL;
	// scene->light = NULL;

	// scene->spheres = NULL;
	// scene->planes = NULL;
	// scene->cylinders = NULL;

	scene->mlx = mlx_init();
	if (scene->mlx == NULL)
		ft_error(-1);
	// mlx->init = kd_nn(mlx_init(), "Error\nmlx_init() is null\n");
	scene->window = mlx_new_window(scene->mlx, scene->width, scene->height, WINDOW_NAME);
	if (scene->window == NULL)
		ft_error(-1);
	scene->img = kd_calloc(1, sizeof(t_img));
	if (scene->img == NULL)
		ft_error(-1);
	scene->img->img = mlx_new_image(scene->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (scene->img->img == NULL)
		ft_error(-1);
	scene->img->addr = mlx_get_data_addr(scene->img->img, &scene->img->bits_per_pixel,
										 &scene->img->bytes_per_line, &scene->img->endian);
	if (scene->img->addr == NULL)
		ft_error(-1);
	scene->img2 = kd_calloc(1, sizeof(t_img));
	if (scene->img2 == NULL)
		ft_error(-1);
	scene->img2->img = mlx_new_image(scene->mlx, scene->width, scene->height);
	if (scene->img2->img == NULL)
		ft_error(-1);
	scene->img2->addr = mlx_get_data_addr(scene->img2->img, &scene->img2->bits_per_pixel,
										 &scene->img2->bytes_per_line, &scene->img2->endian);
	if (scene->img2->addr == NULL)
		ft_error(-1);
	return (scene);
	// mlx_put_image_to_window(scene->mlx, scene->window, scene->img, 0, 0);
	// mlx_destroy_image(scene->mlx, scene->img);
}


// sp 0,0,20.6 12.6 10,0,255

void	parse_line(t_scene *scene, char *str)
{
	// char	**subs;

	// subs = ft_split(str, ' ');
	while (ft_isspace(*str))
		str++;
	if (str[0] == 's' && str[1] == 'p')
		add_sphere(scene, &str[2]);
	else if (str[0] == 'p' && str[1] == 'l')
		add_plane(scene, &str[2]);
	else if (str[0] == 'c' && str[1] == 'y')
		add_cylinder(scene, &str[2]);
	else if (str[0] == 'C')
		add_camera(scene, &str[1]);
	else if (str[0] == 'A')
		add_ambient(scene, &str[1]);
	else if (str[0] == 'L')
		add_light(scene, &str[1]);



	else if (str[0] == '\0')
		;
	else
		ft_error(5);

	// free_after_split(subs);
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
		// savepoint = str; //we need a savepoint because 
		parse_line(scene, str);
		free(str); 
		str = get_next_line(fd);
	}
	return (scene);

}