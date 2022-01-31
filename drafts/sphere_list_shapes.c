/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: konstanting <konstanting@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:30:30 by lajudy            #+#    #+#             */
/*   Updated: 2022/01/31 22:56:36 by konstanting      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// float	get_sp_radius(char **str)
// {
// 	float	res;

// 	res = ft_atof(*str);
// }

// sp 0,0,20.6 12.6 10,0,255
//return -1 in case of invalid data
void	add_sphere(t_scene *scene, char *str)
{
	t_sphere	*sphere;
	t_vector	*center;
	t_color		*color;
	float		diametr;
	int			err;

	err = 0;
	center = new_vector_atof(&str, &err);
	printf("***add_sphere***\n");
	printf("center->x:%f\n", center->x);
	printf("err:%d\n", err);
	printf("center->y:%f\n", center->y);
	printf("err:%d\n", err);
	printf("center->z:%f\n", center->z);
	printf("err:%d\n", err);
	// center = new_vector(3, 2, -32.8);
	diametr = ft_atof(&str, &err);
	printf("diametr:%f\n", diametr);
	printf("err:%d\n", err);

	color = new_color_atoc(&str, &err);
	printf("color->r:%d\n", color->r);
	printf("color->g:%d\n", color->g);
	printf("color->b:%d\n", color->b);

	printf("err:%d\n", err);
	check_endline(&str, &err);
	printf("err:%d\n", err);
	if (err)
		ft_error(3);
	sphere = new_sphere(center, diametr / 2, color);
	add_shape_front(&scene->shapes, SPHERE, sphere);

	// return (1);
}

t_sphere	*new_sphere(t_vector *center, double radius, t_color *color)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (sphere == NULL)
		ft_error(-1);
	sphere->center = center;
	sphere->radius = radius;
	sphere->next = NULL;
	sphere->color = color;
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