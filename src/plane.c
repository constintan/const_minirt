/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:30:30 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/01 22:19:55 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	intersect_plane2(t_plane *plane, t_ray *ray, t_bool bump,
	t_scene *scene)
{
	ray->coordinates = matrix3_addition(ray->position, vector3_multiply(
				ray->orient, ray->t));
	ray->color = plane->color;
	texture_plane(plane, ray, bump, scene);
}

//https://www.scratchapixel.com/lessons/3d-basic-rendering/
//minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
void	intersect_plane(t_plane *plane, t_ray *ray, t_bool bump, t_scene *scene)
{
	double		denom;
	double		t;

	denom = vector3_scalar(plane->orient, ray->orient);
	if (denom > EPSILON)
	{
		t = vector3_scalar(matrix3_subtract(plane->position, ray->position),
				plane->orient) / denom;
		if (t < EPSILON || (t + EPSILON > ray->t))
			return ;
		ray->normal = vector3_negate(plane->orient);
	}
	else if (denom < -EPSILON)
	{
		denom = vector3_scalar(vector3_negate(plane->orient), ray->orient);
		t = vector3_scalar(matrix3_subtract(plane->position, ray->position),
				vector3_negate(plane->orient)) / denom;
		if (t < EPSILON || (t + EPSILON > ray->t))
			return ;
		ray->normal = plane->orient;
	}
	else
		return ;
	ray->t = t;
	intersect_plane2(plane, ray, bump, scene);
}

void	add_plane(t_scene *scene, char *str)
{
	t_plane		*plane;
	t_vector3	position;
	t_vector3	orient;
	t_color		color;
	int			err;

	err = 0;
	position = new_vector_atof(&str, &err);
	orient = new_vector_atof(&str, &err);
	check_direction_limits(orient, &err);
	color = new_color_atoc(&str, &err);
	check_endline(&str, &err);
	if (err)
		ft_error(8);
	plane = new_plane(position, orient, color);
	plane->next = scene->planes;
	scene->planes = plane;
}

t_plane	*new_plane(t_vector3 position, t_vector3 orient, t_color color)
{
	t_plane	*plane;

	plane = kd_calloc(1, sizeof(t_plane));
	if (plane == NULL)
		ft_error(-1);
	plane->position = position;
	plane->orient = vector3_normalise(orient);
	plane->color = color;
	return (plane);
}
