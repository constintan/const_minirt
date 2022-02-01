/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:08:54 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/01 22:24:30 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3 new_vector_atof(char **str, int *err)
{
	double x;
	double y;
	double z;

	x = ft_atof(str, err);
	while (ft_isspace(**str))
		(*str)++;
	if (**str == ',')
		(*str)++;
	y = ft_atof(str, err);
	while (ft_isspace(**str))
		(*str)++;
	if (**str == ',')
		(*str)++;
	z = ft_atof(str, err);
	return (new_vector(x, y, z));
}
// new_vector(ft_atof(&str, &err), ft_atof(&str, &err), ft_atof(&str, &err))

t_vector3 new_vector(double x, double y, double z)
{
	t_vector3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vector3 vec_subtract(t_vector3 vec1, t_vector3 vec2)
{
	t_vector3 result;

	result = new_vector(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
	return (result);
}

double	vec_length(t_vector3	vec)
{
	double	result;

	result = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	return (result);
}

void	vec_normalize(t_vector3 vec)
{
	double	length;

	length = vec_length(vec);
	vec.x = vec.x / length;
	vec.y = vec.y / length;
	vec.z = vec.z / length;
}

double	vec_dot_product(t_vector3 v1, t_vector3 v2)
{
	double	result;

	result = ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
	return (result);
}

