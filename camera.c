/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:35:11 by lajudy            #+#    #+#             */
/*   Updated: 2022/01/29 01:26:03 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_direction_limits(t_vector *direction, int *err)
{
	if (direction->x < -1 || direction->x > 1 )
		*err = 1;
	if (direction->y < -1 || direction->y > 1 )
		*err = 1;
	if (direction->z < -1 || direction->z > 1 )
		*err = 1;
}

void	add_camera(t_scene *scene, char *str)
{
	t_vector	*origin;
	t_vector	*direction;
	double		fov;

	int			err;

	if (scene->camera != NULL)
		ft_error(4);
	err = 0;
	origin = new_vector_atof(&str, &err);
	printf("***add_camera***\n");
	printf("origin->x:%f\n", origin->x);
	printf("err:%d\n", err);
	printf("origin->y:%f\n", origin->y);
	printf("err:%d\n", err);
	printf("origin->z:%f\n", origin->z);
	printf("err:%d\n", err);
	direction = new_vector_atof(&str, &err);
	printf("direction->x:%f\n", direction->x);
	printf("err:%d\n", err);
	printf("direction->y:%f\n", direction->y);
	printf("err:%d\n", err);
	printf("direction->z:%f\n", direction->z);
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

t_camera	*new_camera(t_vector *origin, t_vector *direction, double fov)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	if (camera == NULL)
		ft_error(-1);
	camera->origin = origin;
	camera->direction = direction;
	camera->fov = fov;
	return (camera);
}
