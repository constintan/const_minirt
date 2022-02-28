/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:30:30 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/12 14:36:45 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	bump(t_ray *ray, double u, double v, t_scene *scene)
{
	ray->normal = vector3_qrotate(ray->normal, sin(u * M_PI_2 * 360) * 10,
			vector3_cw(ray->normal));
	ray->normal = vector3_qrotate(ray->normal, sin(v * M_PI_2 * 180) * 10,
			vector3_cw(ray->normal));
	(void)scene;
}

static t_color	texture_sphere(t_sphere *sphere, t_ray *ray, t_scene *scene)
{
	double	uf;
	double	vf;
	double	u;
	double	v;

	if (!scene->checkerboard && !scene->bump)
		return (sphere->color);
	u = 0.5 + atan2((ray->coordinates.z - sphere->position.z) / sphere->radius,
			(ray->coordinates.x - sphere->position.x) / sphere->radius)
		/ (2 * M_PI);
	v = 0.5 - asin((ray->coordinates.y - sphere->position.y) / sphere->radius)
		/ M_PI;
	if (scene->bump)
		bump(ray, u, v, scene);
	if (!scene->checkerboard)
		return (sphere->color);
	uf = floor(fmod(u * 18, 2));
	vf = floor(fmod(v * 9, 2));
	if ((uf && vf) || (!uf && !vf))
		return (new_color(255, 255, 255));
	else
		return (new_color(0, 0, 0));
}

//https://www.ccs.neu.edu/home/fell/CS4300/Lectures/Ray-TracingFormulas.pdf
void	intersect_sphere(t_sphere *sphere, t_ray *r, t_scene *scene)
{
	t_ray		tmp_ray;
	t_vector3	d;
	t_vector3	p;
	t_quad		q;

	d = r->orient;
	p = matrix3_subtract(r->position, sphere->position);
	q.a = vector3_sumpow2(d);
	q.b = 2 * d.x * p.x + 2 * d.y * p.y + 2 * d.z * p.z;
	q.c = vector3_sumpow2(sphere->position) + vector3_sumpow2(r->position)
		- 2 * vector3_scalar(sphere->position, r->position)
		- pow(sphere->radius, 2);
	tmp_ray = *r;
	tmp_ray.t = math_quadratic_equation(&q);
	if (tmp_ray.t < EPSILON || tmp_ray.t + EPSILON > r->t)
		return ;
	*r = tmp_ray;
	r->coordinates = matrix3_addition(r->position, vector3_multiply(d, r->t));
	if (fmin(q.t1, q.t2) > EPSILON)
		r->normal = vector3_normalise(matrix3_subtract(r->coordinates,
					sphere->position));
	else
		r->normal = vector3_normalise(matrix3_subtract(sphere->position,
					r->coordinates));
	r->color = texture_sphere(sphere, r, scene);
}

void	add_sphere(t_scene *scene, char *str)
{
	t_sphere	*sphere;
	t_vector3	center;
	t_color		color;
	float		diametr;
	int			err;

	err = 0;
	center = new_vector_atof(&str, &err);
	diametr = ft_atof(&str, &err);
	color = new_color_atoc(&str, &err);
//	check_endline(&str, &err);
	if (err)
		ft_error(3);
	sphere = new_sphere(center, diametr / 2, color);
	sphere->next = scene->spheres;
	scene->spheres = sphere;
}

t_sphere	*new_sphere(t_vector3 position, double radius, t_color color)
{
	t_sphere	*sphere;

	sphere = kd_calloc(1, sizeof(t_sphere));
	if (sphere == NULL)
		ft_error(-1);
	sphere->position = position;
	sphere->radius = radius;
	sphere->color = color;
	return (sphere);
}
