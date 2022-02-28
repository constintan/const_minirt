/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:35:11 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/11 01:21:51 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_direction_limits(t_vector3 orient, int *err)
{
	if (orient.x < -1 || orient.x > 1)
		*err = 1;
	if (orient.y < -1 || orient.y > 1)
		*err = 1;
	if (orient.z < -1 || orient.z > 1)
		*err = 1;
}

void	add_camera(t_scene *scene, char *str)
{
	t_camera	*camera;
	t_vector3	origin;
	t_vector3	direction;
	double		fov;
	int			err;

	err = 0;
	origin = new_vector_atof(&str, &err);
	direction = new_vector_atof(&str, &err);
	check_direction_limits(direction, &err);
	while (ft_isspace(*str))
		(str)++;
	if (*str == '\0')
		fov = DEFAULT_FOV;
	else
	{
		fov = ft_atof(&str, &err);
		if (fov < 0 || fov > 180)
			err = 1;

	}
	check_endline(&str, &err);
	if (err)
		ft_error(4);
	camera = new_camera(origin, direction, fov);
	scene->camera = new_camera(origin, direction, fov);
	camera->next = scene->camera;
	scene->camera = camera;
}

void	reset_camera(t_scene *scene)
{
	scene->camera->position = scene->camera->defaults->position;
	scene->camera->orient = scene->camera->defaults->orient;
	scene->camera->rotate = scene->camera->defaults->rotate;
	scene->camera->fov = scene->camera->defaults->fov;
	scene->camera->zoom = scene->camera->defaults->zoom;
	redraw_frame(scene);
}

static t_camera	*copy_camera(t_vector3 position, t_vector3 orient, double fov)
{
	t_camera	*camera;

	camera = kd_calloc(1, sizeof(t_camera));
	if (camera == NULL)
		ft_error(-1);
	camera->position = position;
	camera->orient = new_vector3(0, 0, 1);
	camera->rotate = vector3_arotate(vector3_normalise(orient), camera->orient);
	camera->rotate_origin = position;
	camera->fov = fov;
	camera->zoom = DEFAULT_ZOOM;
	return (camera);
}

t_camera	*new_camera(t_vector3 position, t_vector3 orient, double fov)
{
	t_camera	*camera;

	camera = kd_calloc(1, sizeof(t_camera));
	if (camera == NULL)
		ft_error(-1);
	camera->position = position;
	camera->orient = new_vector3(0, 0, 1);
	camera->rotate = vector3_arotate(vector3_normalise(orient), camera->orient);
	camera->rotate_origin = position;
	camera->fov = fov;
	camera->zoom = DEFAULT_ZOOM;
	camera->defaults = copy_camera(position, orient, fov);
	return (camera);
}
