/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:35:11 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/02 00:29:00 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_direction_limits(t_vector3 orient, int *err)
{
	if (orient.x < -1 || orient.x > 1 )
		*err = 1;
	if (orient.y < -1 || orient.y > 1 )
		*err = 1;
	if (orient.z < -1 || orient.z > 1 )
		*err = 1;
}

void	add_camera(t_scene *scene, char *str)
{
	t_vector3	origin;
	t_vector3	direction;
	double		fov;

	int			err;

	if (scene->camera != NULL)
		ft_error(4);
	err = 0;
	origin = new_vector_atof(&str, &err);
	printf("***add_camera***\n");
	printf("origin.x:%f\n", origin.x);
	printf("err:%d\n", err);
	printf("origin.y:%f\n", origin.y);
	printf("err:%d\n", err);
	printf("origin.z:%f\n", origin.z);
	printf("err:%d\n", err);
	direction = new_vector_atof(&str, &err);
	printf("direction.x:%f\n", direction.x);
	printf("err:%d\n", err);
	printf("direction.y:%f\n", direction.y);
	printf("err:%d\n", err);
	printf("direction.z:%f\n", direction.z);
	printf("err:%d\n", err);

	check_direction_limits(direction, &err);
	fov = ft_atof(&str, &err);
	if (fov < 0 || fov > 180)
		err = 1;
	printf("fov:%f\n", fov);
	printf("err:%d\n", err);
	check_endline(&str, &err);
	printf("err:%d\n", err);
	if (err)
		ft_error(4);
	scene->camera = new_camera(origin, direction, fov);
}

t_camera	*new_camera(t_vector3 position, t_vector3 orient, double fov)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	if (camera == NULL)
		ft_error(-1);
	camera->position = position;
	camera->orient = new_vector3(0, 0, 1);
	camera->rotate = vector3_arotate(vector3_normalise(orient), camera->orient);
	camera->fov = fov;
	camera->zoom = DEFAULT_ZOOM;
	return (camera);
}
