/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:12:06 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/12 15:52:25 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	*clean_shapes(void *shape, void *next)
{
	kd_free(shape);
	return (next);
}

void	next_scene(t_scene *scene)
{
	scene->light = kd_free(scene->light);
	scene->ambient = kd_free(scene->ambient);
	scene->camera->defaults = kd_free(scene->camera->defaults);
	scene->camera = kd_free(scene->camera);
	while (scene->spheres)
		scene->spheres = clean_shapes(scene->spheres, scene->spheres->next);
	while (scene->planes)
		scene->planes = clean_shapes(scene->planes, scene->planes->next);
	while (scene->cylinders)
		scene->cylinders = clean_shapes(scene->cylinders,
				scene->cylinders->next);
	while (scene->cones)
		scene->cones = clean_shapes(scene->cones, scene->cones->next);
	if (!scene->maps[++scene->map_index])
	{
		printf("This was the last scene...\n");
		scene->map_index = 0;
	}
	printf("Starting scene: %s\n", scene->maps[scene->map_index]);
	scene_init(scene->maps[scene->map_index], scene);
	redraw_frame(scene);
}
