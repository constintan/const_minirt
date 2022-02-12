/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/12 14:42:47 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// лучи из камеры, поиск места пересечения с фигурами
// в функцию приходит пустой ray, функция считает шаг в отосительных
// координатах и формирует
//step -- перевод из координат mlx в координаты сцены (из обсолютных
// координат пиксельной матрицы, а относительным координатам сцены [-1; 1])
void	raytrace(int x, int y, t_ray *ray, t_scene *scene)
{
	t_vector2	step;

	step = new_vector2((x - scene->width / (double)2) / scene->width
			* (double)2, -(y - scene->height / (double)2) / scene->width
			* (double)2);
	if (scene->view == 0)
		ray_orthographic(scene->camera, step, ray);
	if (scene->view == 1)
		ray_perspective_tan(scene->camera, step, ray);
	else if (scene->view == 2)
		ray_perspective_spherise(scene->camera, step, ray);
	else if (scene->view == 3)
		ray_perspective_spherise2(scene->camera, step, ray);
	else if (scene->view == 4)
		ray_perspective_spherise3(scene->camera, step, ray);
	else if (scene->view == 5)
		ray_perspective_quaternion(scene, x, y, ray);
	else if (scene->view == 6)
		ray_perspective_quaternion2(scene, x, y, ray);
	intersect(ray, scene);
}

// включает поворот камеры, если флаг play активирован
//printf("c u %f v %f\n", scene->camera->rotate.u, scene->camera->rotate.v);
void	animate(t_scene *scene)
{
	if (scene->play)
	{
		scene->everynframe = scene->minquality;
		scene->idle = 0;
		scene->rays_set = FALSE;
		scene->gamma = 1;
		if (scene->play == 3)
		{
			rotate_camera_xz(scene->camera, -10);
			rotate_camera_y(scene->camera, 10);
		}
		else if (scene->play == 2)
			rotate_camera_xz(scene->camera, -10);
		else if (scene->play == 1)
			rotate_camera_y(scene->camera, 10);
		else
			scene->play = 0;
	}
}

void	update_window(t_scene *scene)
{
	if (!scene->oddframe)
	{
		mlx_put_image_to_window(scene->mlx, scene->window, scene->img->img,
			0, 0);
		scene->oddframe = 1;
	}
	else
	{
		mlx_put_image_to_window(scene->mlx, scene->window, scene->img2->img,
			0, 0);
		scene->oddframe = 0;
	}
	hud(scene);
}

void	iterate_pixels_gamma_correction(t_scene *scene)
{
	t_ray	*ray;
	int		x;
	int		y;

	y = 0;
	while (y < scene->height)
	{
		x = 0;
		while (x < scene->width)
		{
			ray = &scene->rays[y * scene->width + x];
			if (x % scene->everynframe == 0
				&& y % scene->everynframe == 0)
				draw_pixel(scene, x, y, colour_gamma_apply(ray->color, scene));
			x++;
		}
		y++;
	}
}

void	reset_rays(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->width * scene->height)
		scene->rays[i++].t = 0;
	scene->rays_set = TRUE;
}
