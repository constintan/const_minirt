/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: konstanting <konstanting@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/01 23:10:19 by konstanting      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	temp_parse_map(t_mlx *mlx)
{
	t_obj	*obj;
//	t_light	*light;

	mlx->ambient = kd_calloc(1, sizeof(t_obj));
	mlx->ambient->bright = 0.2;
	mlx->ambient->color.r = 255;
	mlx->ambient->color.g = 255;
	mlx->ambient->color.b = 255;
	mlx->camera = kd_calloc(1, sizeof(t_obj));
	mlx->camera->position.x = 0;
	mlx->camera->position.y = 20;
	mlx->camera->position.z = -50;
	mlx->camera->orient.x = 0;
	mlx->camera->orient.y = 0;
	mlx->camera->orient.z = 1;
	mlx->camera->rotate.u = 0;
	mlx->camera->rotate.v = 0;
	mlx->camera->fov = 70;
	mlx->camera->zoom = 32;
	mlx->light = kd_calloc(1, sizeof(t_obj));
	mlx->light->position.x = -10;
	mlx->light->position.y = 15;
	mlx->light->position.z = -10;
	mlx->light->bright = 0.8;
	mlx->light->color.r = 255;
	mlx->light->color.g = 255;
	mlx->light->color.b = 255;

//	mlx->light->next = kd_calloc(1, sizeof(t_obj));
//	light = mlx->light->next;
////	light = mlx->light;
//	light->position.x = -5;
//	light->position.y = 35;
//	light->position.z = -10;
//	light->value = 0.9;
//	light->colour.red = 0;
//	light->colour.green = 255;
//	light->colour.blue = 0;
//
//	light->next = kd_calloc(1, sizeof(t_obj));
//	light = light->next;
////	light = mlx->light;
//	light->position.x = 0;
//	light->position.y = 35;
//	light->position.z = -25;
//	light->value = 0.9;
//	light->colour.red = 0;
//	light->colour.green = 0;
//	light->colour.blue = 255;

	mlx->obj = kd_calloc(1, sizeof(t_obj));
	obj = mlx->obj;
	obj->type = PLANE;
	obj->position.x = 0;
	obj->position.y = 0;
	obj->position.z = 0;
	obj->orientation.x = 0;
	obj->orientation.y = 1;
	obj->orientation.z = 0;
	obj->colour.r = 128;
	obj->colour.g = 128;
	obj->colour.b = 128;

	obj->next = kd_calloc(1, sizeof(t_obj));
	obj = obj->next;
	obj->type = PLANE;
	obj->position.x = 100;
	obj->position.y = 0;
	obj->position.z = 0;
	obj->orientation.x = 1;
	obj->orientation.y = 0;
	obj->orientation.z = 0;
	obj->colour.r = 100;
	obj->colour.g = 0;
	obj->colour.b = 225;

	obj->next = kd_calloc(1, sizeof(t_obj));
	obj = obj->next;
	obj->type = SPHERE;
	obj->position.x = 0;
	obj->position.y = 20;
	obj->position.z = 0;
	obj->diameter = 20;
	obj->colour.r = 128;
	obj->colour.g = 128;
	obj->colour.b = 128;

	obj->next = kd_calloc(1, sizeof(t_obj));
	obj = obj->next;
	obj->type = SPHERE;
	obj->position.x = 0;
	obj->position.y = 20;
	obj->position.z = -100;
	obj->diameter = 20;
	obj->colour.r = 255;
	obj->colour.g = 255;
	obj->colour.b = 0;

	obj->next = kd_calloc(1, sizeof(t_obj));
	obj = obj->next;
	obj->type = SPHERE;
	obj->position.x = 0;
	obj->position.y = 20;
	obj->position.z = -100;
	obj->diameter = 20000;
	obj->colour.r = 255;
	obj->colour.g = 255;
	obj->colour.b = 0;

	obj->next = kd_calloc(1, sizeof(t_obj));
	obj = obj->next;
	obj->type = SPHERE;
	obj->position.x = 5;
	obj->position.y = 10;
	obj->position.z = -100;
	obj->diameter = 20;
	obj->colour.r = 155;
	obj->colour.g = 255;
	obj->colour.b = 100;

	obj->next = kd_calloc(1, sizeof(t_obj));
	obj = obj->next;
	obj->type = CYLINDER;
	obj->position.x = 50;
	obj->position.y = 0;
	obj->position.z = 20.6;
	obj->orientation.x = 0;
	obj->orientation.y = 0;
	obj->orientation.z = 1;
	obj->diameter = 14.2;
	obj->height = 21.42;
	obj->colour.r = 10;
	obj->colour.g = 0;
	obj->colour.b = 255;
	mlx->camera->orient = vector3_normalise(mlx->camera->orient);
	obj = mlx->obj;
	while (obj)
	{
		if (obj->type == PLANE || obj->type == CYLINDER)
			obj->orientation = vector3_normalise(obj->orientation);
		if (obj->type == SPHERE || obj->type == CYLINDER)
			obj->radius = obj->diameter / 2;
		if (obj->type == SPHERE)
			obj->max_distance = 0;//vector3_distance(obj->position, mlx->camera->position) + obj->radius;
		if (obj->type == CYLINDER)
			obj->max_distance = vector3_distance(obj->position, mlx->camera->position) + sqrt(pow(obj->radius, 2) + pow(obj->height, 2));
		obj = obj->next;
	}
}

void	minirt(int argc, char **argv)
{
	// t_mlx	*mlx;
	t_scene *scene;

	if (argc == 1 || invalid_filename(argv[1]))
		ft_error(1);

	scene = scene_init(argv[1]);

	// ray_tracing(scene);
	create_window(scene);
	// mlx_loop(scene->mlx);

	// mlx = kd_calloc(1, sizeof(t_mlx));
	// mlx->win_w = 640;
	// mlx->win_h = 480;

	// temp_parse_map(mlx);

	// mlx->maps = maps;
	// mlx->map_index = 0;

	// mlx->init = kd_nn(mlx_init(), "Error\nmlx_init() is null\n");
}
