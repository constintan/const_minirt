/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/12 01:33:05 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	iterate_pixels(t_scene *scene)
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
			if (x % scene->everynframe == 0 &&
				y % scene->everynframe == 0)
			{
				if (!ray->t)
				{
					ray->t = INFINITY;
					raytrace(x, y, ray, scene);
					compute_light(ray, scene);
				}
			}
			x++;
		}
		y++;
	}
}

int	render_next_frame(t_scene *scene)
{
	animate(scene);
	if (scene->idle > 0)
	{
		scene->idle--;
		return (0);
	}
	else if (scene->idle < 0)
		return (0);
//	scene->hud = kd_strf("x %d y %d", (int)scene->camera->rotate.u, (int)scene->camera->rotate.v);
	if (!scene->rays_set)
		reset_rays(scene);
	iterate_pixels(scene);
	iterate_pixels_gamma_correction(scene);
	update_window(scene);
	scene->idle = 1;
	if (scene->everynframe >= 20)
		scene->everynframe /= 2;
	else if (scene->everynframe > 10)
		scene->everynframe = 10;
	else if (scene->everynframe > scene->maxquality)
		scene->everynframe--;
	else
		scene->idle = -1;
	return (0);
}
