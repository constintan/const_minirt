/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:19:30 by lajudy            #+#    #+#             */
/*   Updated: 2022/01/29 19:50:25 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_scene	*new_scene(void)
{
	t_scene	*scene;


	scene = (t_scene *)malloc(sizeof(t_scene));
	if (scene == NULL)
		ft_error(-1);
	scene->width = WINDOW_WIDTH;
	scene->height = WINDOW_HEIGHT;
	scene->camera = NULL;
	scene->ambient = NULL;
	scene->light = NULL;

	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;

	scene->mlx = mlx_init();
	scene->window = mlx_new_window(scene->mlx, scene->width, scene->height, WINDOW_NAME);
	
	scene->img = mlx_new_image(scene->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	scene->addr = mlx_get_data_addr(scene->img, &scene->bits_per_pixel,
			&scene->bytes_per_line, &scene->endian);
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