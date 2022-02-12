/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/12 14:51:01 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_bool	compute_shadow(t_light *light, t_vector3 l, t_ray *ray,
								t_scene *scene)
{
	t_ray	new_ray;

	new_ray.position = ray->coordinates;
	new_ray.orient = l;
	new_ray.t = INFINITY;
	intersect(&new_ray, scene);
	if (new_ray.t > EPSILON && pow(new_ray.t, 2) + EPSILON < vector3_sumpow2(
			matrix3_subtract(light->position, ray->coordinates)))
		return (TRUE);
	return (FALSE);
}

static t_color	apply_light(t_color object, t_color light, double intensity)
{
	return (colour_matrix_amplify(object, colour_amplify(light, intensity)));
}

void	compute_light(t_ray *ray, t_scene *scene)
{
	t_light		*light;
	t_vector3	l;
	double		fctr;
	t_color		color;
	double		hf;
	t_vector3	h;
	double		n;

	if (ray->t == INFINITY)
	{
		ray->color = new_color(DEF_BG_COLOR_R, DEF_BG_COLOR_G, DEF_BG_COLOR_B);
		return ;
	}
	color = apply_light(ray->color, scene->ambient->color,
			scene->ambient->bright);
	light = scene->light;
	while (light && !scene->no_lights)
	{
		if (!scene->one_light || scene->current_light == light)
		{
			l = vector3_normalise(
					matrix3_subtract(light->position, ray->coordinates));
			fctr = vector3_scalar(ray->normal, l);
			//перпендикулярный нормаль к свету = 0, параллельный = 1
			if (fctr < 0 || (!scene->no_shadows
					&& compute_shadow(light, l, ray, scene)))
				fctr = 0;
			color = colour_add(color, colour_amplify(apply_light(
							ray->color, light->color, light->bright), fctr));
			//блики
			if (!scene->no_specular && fctr)
			{
				h = vector3_normalise(matrix3_addition(
							vector3_negate(ray->orient), l));
				n = 16;
				hf = vector3_scalar(h, ray->normal) * sin(M_PI_2 * sin(M_PI_2
							* sin(M_PI_2 * sin(M_PI_2 * fctr))));
				if (hf > 0)
					color = colour_add(color, colour_amplify(apply_light(color,
									light->color, light->bright), pow(hf, n)));
			}
		}
		light = light->next;
	}
	ray->color = colour_gamma_collect(color, scene);
}
