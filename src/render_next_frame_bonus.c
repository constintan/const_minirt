/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/12 01:44:23 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minirt_bonus.h"

static void	iterate_pixels(t_scene *scene, t_thread *thread)
{
	t_ray	*ray;
	int		x;
	int		y;

	y = thread->index * scene->everynframe;
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
		y = y + THREADS * scene->everynframe;
	}
}

void	*thread_loop(void *thread_void)
{
	t_scene *scene;
	t_thread *thread;
	t_bonus *bonus;

	thread = thread_void;
	scene = thread->scene;
	bonus = scene->bonus;
	while (1)
	{
		sem_wait(bonus->threads1);
		sem_post(bonus->threads2);
		iterate_pixels(scene, thread);
		printf("thread %d finished %d quality\n", thread->index, scene->everynframe);
		sem_wait(bonus->threads3);
		sem_post(bonus->threads4);
	}
	return (NULL);
}

int	render_next_frame_bonus(t_scene *scene)
{
	int	i;
	t_bonus	*bonus;

	bonus = scene->bonus;
	animate(scene);
	if (scene->idle > 0)
	{
		scene->idle--;
		return (0);
	}
	else if (scene->idle < 0)
		return (0);
	bonus->timestamp = mtv();
	if (!scene->rays_set)
		reset_rays(scene);
	i = 0;
	while (i++ < THREADS)
		sem_post(bonus->threads1);
	i = 0;
	while (i++ < THREADS)
		sem_wait(bonus->threads2);
	i = 0;
	while (i++ < THREADS)
		sem_post(bonus->threads3);
	i = 0;
	while (i++ < THREADS)
		sem_wait(bonus->threads4);
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
