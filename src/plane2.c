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

static char	*texture_plane_get_addr(t_img *img, t_vector2 tile)
{
	return (img->addr + ((int)fmod(fmod(tile.v, img->height) + img->height,
				img->height) * img->bytes_per_line + (int)fmod(fmod(tile.u,
					img->width) + img->width, img->width) * (img->bits_per_pixel
				/ 8)));
}

void	texture_plane(t_plane *plane, t_ray *ray, t_bool bump, t_scene *scene)
{
	t_pl		pl;

	if (!bump)
		return ;
	pl.local = matrix3_subtract(ray->coordinates, plane->position);
	pl.ulocal = vector3_normalise(pl.local);
	pl.costheta = vector3_scalar(pl.ulocal, vector3_cw(plane->orient));
	pl.tile.u = sqrt(vector3_sumpow2(pl.local)) * pl.costheta * 100;
	pl.costheta = vector3_scalar(pl.ulocal, vector3_ccw(plane->orient));
	pl.tile.v = sqrt(vector3_sumpow2(pl.local)) * pl.costheta * 100;
	pl.dst = texture_plane_get_addr(scene->texturemap, pl.tile);
	ray->color = new_color((*(unsigned int *)pl.dst & 0x00ff0000) >> 16,
			(*(unsigned int *)pl.dst & 0x0000ff00) >> 8,
			(*(unsigned int *)pl.dst & 0x000000ff));
	pl.dst = texture_plane_get_addr(scene->bumpmap, pl.tile);
	pl.color = new_vector3((*(unsigned int *)pl.dst & 0x00ff0000) >> 16,
			(*(unsigned int *)pl.dst & 0x0000ff00) >> 8,
			(*(unsigned int *)pl.dst & 0x000000ff));
	pl.color.x = (pl.color.x / 255 - 0.5) * 2;
	pl.color.y = (pl.color.y / 255 - 0.5) * 2;
	pl.color.z = (pl.color.z / 255 - 0.5) * 2;
	ray->normal = vector3_qrotate(vector3_qrotate(ray->normal, pl.color.y
				* 90, vector3_cw(plane->orient)), pl.color.x * -90,
			vector3_ccw(plane->orient));
}
