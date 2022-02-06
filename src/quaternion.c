/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/05 23:29:14 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	quaternion_sumpow2(t_quaternion q)
{
	return (pow(q.w, 2) + pow(q.i, 2) + pow(q.j, 2) + pow(q.k, 2));
}

t_quaternion	quaternion_normalise(t_quaternion q)
{
	double	magnitude;

	magnitude = quaternion_sumpow2(q);
	if (magnitude == 1)
		return (q);
	magnitude = sqrt(magnitude);
	if (magnitude > 0)
	{
		q.w /= magnitude;
		q.i /= magnitude;
		q.j /= magnitude;
		q.k /= magnitude;
	}
	return (q);
}

t_quaternion	new_quaternion(double theta, t_vector3 axis)
{
	t_quaternion	q;
	double			st;

	theta /= 2;
	st = sin(theta);
	axis = vector3_normalise(axis);
	q.w = cos(theta);
	q.i = axis.x * st;
	q.j = axis.y * st;
	q.k = axis.z * st;
	return (quaternion_normalise(q));
}