/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:30:30 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/01 22:22:43 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_sphere(t_scene *scene, char *str)
{
	t_sphere	*sphere;
	t_vector3	center;
	t_color		color;
	float		diametr;
	int			err;

	err = 0;
	center = new_vector_atof(&str, &err);
	printf("***add_sphere***\n");
	printf("center.x:%f\n", center.x);
	printf("err:%d\n", err);
	printf("center.y:%f\n", center.y);
	printf("err:%d\n", err);
	printf("center.z:%f\n", center.z);
	printf("err:%d\n", err);
	// center = new_vector(3, 2, -32.8);
	diametr = ft_atof(&str, &err);
	printf("diametr:%f\n", diametr);
	printf("err:%d\n", err);

	color = new_color_atoc(&str, &err);
	printf("color->r:%d\n", color.r);
	printf("color->g:%d\n", color.g);
	printf("color->b:%d\n", color.b);

	printf("err:%d\n", err);
	check_endline(&str, &err);
	printf("err:%d\n", err);
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
