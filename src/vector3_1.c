/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/08 15:40:09 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3	matrix3_subtract(t_vector3 a, t_vector3 b)
{
	t_vector3	difference;

	difference.x = a.x - b.x;
	difference.y = a.y - b.y;
	difference.z = a.z - b.z;
	return (difference);
}

t_vector3	matrix3_addition(t_vector3 a, t_vector3 b)
{
	t_vector3	sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	sum.z = a.z + b.z;
	return (sum);
}

double	vector3_distance(t_vector3 a, t_vector3 b)
{
	double		distance;
	t_vector3	difference;

	difference = matrix3_subtract(a, b);
	distance = sqrt(vector3_sumpow2(difference));
	return (distance);
}

t_vector3	vector3_normalise(t_vector3 direction)
{
	double	magnitude;

	magnitude = vector3_sumpow2(direction);
	if (magnitude == 1)
		return (direction);
	magnitude = sqrt(magnitude);
	if (magnitude > 0)
	{
		direction.x /= magnitude;
		direction.y /= magnitude;
		direction.z /= magnitude;
	}
	return (direction);
}
