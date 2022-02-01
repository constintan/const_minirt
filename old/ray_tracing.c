/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: konstanting <konstanting@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:51:17 by lajudy            #+#    #+#             */
/*   Updated: 2022/01/31 23:38:33 by konstanting      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_screen	*new_screen(double width, double height, double fov)
{
	t_screen	*screen;
	double		ratio;

	screen = (t_screen *)malloc(sizeof(t_screen));
	if (screen == NULL)
		ft_error(-1);
	ratio = width / height;
	screen->width = 2 * tan(fov / 2 * (M_PI / 180));
	screen->height = screen->width / ratio;
	screen->x_step = screen->width / width;
	screen->y_step = screen->height / height;
	return (screen);
}


void	ray_tracing(t_scene *scene)
{
	int			mlx_x;
	int			mlx_y;
	double		x;
	double		y;
	double		x_ray;
	double		y_ray;
	t_color			*color;
	t_vector	*ray;
	t_screen	*screen;

	screen = new_screen(scene->width, scene->height, scene->camera->fov);
	y = scene->height / 2;
	mlx_y = 0;
	while (y > (scene->height / 2 * -1))
	{
		y_ray = y * screen->y_step;
		x = scene->width / 2 * -1;
		mlx_x = 0;
		while (x < scene->width / 2)
		{
			x_ray = x * screen->x_step;
			ray = new_vector(x_ray, y_ray, -1);
			vec_normalize(ray);
			if (sphere_intersect(scene->camera, ray, scene->spheres))
				color = scene->spheres->color;
			else
				color = new_color(DEFAULT_BG_COLOR);
			draw_pixel(scene, mlx_x, mlx_y, color);
			// mlx_pixel_put(scene->mlx, scene->window, mlx_x, mlx_y, color);
			// printf("mlx_x:%d, mlx_y:%d\n", mlx_x, mlx_y);
			free(ray);
			x++;
			mlx_x++;
		}
		y--;
		mlx_y++;
	}
	mlx_put_image_to_window(scene->mlx, scene->window, scene->img, 0, 0);
	mlx_destroy_image(scene->mlx, scene->img);
}
