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

static void	texture_plane(t_plane *plane, t_ray *ray, t_bool bump,
	t_scene *scene)
{
	char		*dst;
	t_vector3	un;
	t_vector3	vn;
	t_vector3	local;
	t_vector3	ulocal;
	double		costheta;
	t_vector2	tile;
	t_vector3	color;
	char		*ddd;

	if (!bump)
		return ;
	un = vector3_cw(plane->orient);
	local = matrix3_subtract(ray->coordinates, plane->position);
	ulocal = vector3_normalise(local);
	costheta = vector3_scalar(ulocal, un);
	tile.u = sqrt(vector3_sumpow2(local)) * costheta * 100;
	vn = vector3_ccw(plane->orient);
	costheta = vector3_scalar(ulocal, vn);
	tile.v = sqrt(vector3_sumpow2(local)) * costheta * 100;
	ddd = scene->texturemap->addr + ((int)fmod(fmod(tile.v,
					scene->bumpmap->height) + scene->bumpmap->height,
				scene->bumpmap->height) * scene->bumpmap->bytes_per_line
			+ (int)fmod(fmod(tile.u, scene->bumpmap->width)
				+ scene->bumpmap->width, scene->bumpmap->width)
			* (scene->bumpmap->bits_per_pixel / 8));
	dst = scene->bumpmap->addr + ((int)fmod(fmod(tile.v, scene->bumpmap->height)
				+ scene->bumpmap->height, scene->bumpmap->height)
			* scene->bumpmap->bytes_per_line + (int)fmod(fmod(tile.u,
					scene->bumpmap->width) + scene->bumpmap->width,
				scene->bumpmap->width) * (scene->bumpmap->bits_per_pixel / 8));
	ray->color = new_color((*(unsigned int *)ddd & 0x00ff0000) >> 16,
			(*(unsigned int *)ddd & 0x0000ff00) >> 8,
			(*(unsigned int *)ddd & 0x000000ff));
	color = new_vector3((*(unsigned int *)dst & 0x00ff0000) >> 16,
			(*(unsigned int *)dst & 0x0000ff00) >> 8,
			(*(unsigned int *)dst & 0x000000ff));
	color.x = (color.x / 255 - 0.5) * 2;
	color.y = (color.y / 255 - 0.5) * 2;
	color.z = (color.z / 255 - 0.5) * 2;
	ray->normal = vector3_qrotate(vector3_qrotate(
				ray->normal, color.y * 90, un), color.x * -90, vn);
}

//https://www.scratchapixel.com/lessons/3d-basic-rendering/
//minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
void	intersect_plane(t_plane *plane, t_ray *ray, t_bool bump, t_scene *scene)
{
	double		denominator;
	double		distance;

	denominator = vector3_scalar(plane->orient, ray->orient);
	if (denominator > EPSILON)
	{
		distance = vector3_scalar(matrix3_subtract(plane->position,
					ray->position), plane->orient) / denominator;
		if (distance < EPSILON || (distance + EPSILON > ray->t))
			return ;
		ray->normal = vector3_negate(plane->orient);
	}
	else if (denominator < -EPSILON)
	{
		denominator = vector3_scalar(vector3_negate(plane->orient),
				ray->orient);
		distance = vector3_scalar(matrix3_subtract(plane->position,
					ray->position), vector3_negate(plane->orient))
			/ denominator;
		if (distance < EPSILON || (distance + EPSILON > ray->t))
			return ;
		ray->normal = plane->orient;
	}
	else
		return ;
	ray->t = distance;
	ray->coordinates = matrix3_addition(ray->position, vector3_multiply(
				ray->orient, distance));
	ray->color = plane->color;
	texture_plane(plane, ray, bump, scene);
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
