/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:30:30 by lajudy            #+#    #+#             */
/*   Updated: 2022/01/27 23:31:11 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// sp 0,0,20.6 12.6 10,0,255
//return -1 in case of invalid data
int	add_sphere(t_scene *scene, char *str)
{
	t_sphere	*sphere;
	t_vector	*center;
	float		radius;

	printf("str:%s\n", str);
	radius = 12.6 / 2;

	center = new_vector(3, 2, -32.8);
	sphere = new_sphere(center, radius);
	sphere->next = scene->spheres;
	scene->spheres = sphere;

	return (1);
}

t_sphere	*new_sphere(t_vector *center, float radius)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (sphere == NULL)
		ft_error(-1);
	sphere->center = center;
	sphere->radius = radius;
	sphere->next = NULL;
	return (sphere);
}

int	sphere_intersect(t_camera *camera, t_vector *ray, t_sphere *sphere)
{
	float		b;
	float		c;
	float		dist1;
	float		dist2;
	float		discrem;
	t_vector	*cam_sphere;

	dist1 = 0;
	dist2 = 0;
	cam_sphere = vec_subtract(camera->origin, sphere->center);
	b = 2 * vec_dot_product(cam_sphere, ray);
	c = vec_dot_product(cam_sphere, cam_sphere) - pow(sphere->radius, 2);
	discrem = pow(b, 2) - 4 * c;
	free(cam_sphere);
	if (discrem < 0)
		return (0);
	dist1 = -b - sqrt(discrem) / 2;
	dist2 = -b + sqrt(discrem) / 2;
	if (dist1 > 0)
		return (1);
	return (0);
}