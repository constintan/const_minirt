/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:08:54 by lajudy            #+#    #+#             */
/*   Updated: 2022/01/27 01:25:56 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector *new_vector(float x, float y, float z)
{
	t_vector	*vec;

	vec = (t_vector *)malloc(sizeof(t_vector));
	if (vec == NULL)
		ft_error(-1);
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}

t_vector	*vec_subtract(t_vector *vec1, t_vector *vec2)
{
	t_vector *result;

	result = new_vector(vec1->x - vec2->x, vec1->y - vec2->y, vec1->z - vec2->z);
	return (result);
}

float	vec_length(t_vector	*vec)
{
	float	result;

	result = sqrt(pow(vec->x, 2) + pow(vec->y, 2) + pow(vec->z, 2));
	return (result);
}

void	vec_normalize(t_vector *vec)
{
	float	length;

	length = vec_length(vec);
	vec->x = vec->x / length;
	vec->y = vec->y / length;
	vec->z = vec->z / length;
}

float	vec_dot_product(t_vector *v1, t_vector *v2)
{
	float	result;

	result = ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
	return (result);
}

