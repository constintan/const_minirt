/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/12 18:47:59 by                  ###   ########.fr       */
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

static void	process_light(t_cl *cl, t_ray *ray, t_scene *scene)
{
	cl->l = vector3_normalise(
			matrix3_subtract(cl->light->position, ray->coordinates));
	cl->fctr = vector3_scalar(ray->normal, cl->l);
	if (cl->fctr < 0 || (!scene->no_shadows
			&& compute_shadow(cl->light, cl->l, ray, scene)))
		cl->fctr = 0;
	cl->color = colour_add(cl->color, colour_amplify(apply_light(
					ray->color, cl->light->color, cl->light->bright),
				cl->fctr));
	if (!scene->no_specular && cl->fctr)
	{
		cl->h = vector3_normalise(matrix3_addition(
					vector3_negate(ray->orient), cl->l));
		cl->n = 16;
		cl->hf = vector3_scalar(cl->h, ray->normal) * sin(M_PI_2
				* sin(M_PI_2 * sin(M_PI_2 * sin(M_PI_2 * cl->fctr))));
		if (cl->hf > 0)
			cl->color = colour_add(cl->color, colour_amplify(apply_light(
							cl->color, cl->light->color,
							cl->light->bright), pow(cl->hf, cl->n)));
	}
}

//блики
//перпендикулярный нормаль к свету = 0, параллельный = 1
void	compute_light(t_ray *ray, t_scene *scene)
{
	t_cl	cl;

	if (ray->t == INFINITY)
	{
		ray->color = new_color(DEF_BG_COLOR_R, DEF_BG_COLOR_G, DEF_BG_COLOR_B);
		return ;
	}
	if (scene->ambient)
		cl.color = apply_light(ray->color, scene->ambient->color,
				scene->ambient->bright);
	else
		cl.color = new_color(0, 0, 0);
	cl.light = scene->light;
	while (cl.light && !scene->no_lights)
	{
		if (!scene->one_light || scene->current_light == cl.light)
		{
			process_light(&cl, ray, scene);
		}
		cl.light = cl.light->next;
	}
	ray->color = colour_gamma_collect(cl.color, scene);
}
