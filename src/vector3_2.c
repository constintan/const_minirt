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

t_vector3	vector3_multiply(t_vector3 direction, double multiply)
{
	direction.x *= multiply;
	direction.y *= multiply;
	direction.z *= multiply;
	return (direction);
}

double	vector3_sumpow2(t_vector3 a)
{
	return (pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
}

double	vector3_scalar(t_vector3 a, t_vector3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector3	vector3_qrotate(t_vector3 a, double theta, t_vector3 axis)
{
	t_vector3		b;
	t_quaternion	q;

	theta = M_PI / 180 * theta;
	q = new_quaternion(theta, axis);
	b.x = a.x * (1 - 2 * (pow(q.j, 2) + pow(q.k, 2))) + a.y * (2 * (q.i * q.j
				- q.k * q.w)) + a.z * (2 * (q.i * q.k + q.j * q.w));
	b.y = a.x * (2 * (q.i * q.j + q.k * q.w)) + a.y * (1 - 2 * (pow(q.i, 2)
				+ pow(q.k, 2))) + a.z * (2 * (q.j * q.k - q.i * q.w));
	b.z = a.x * (2 * (q.i * q.k - q.j * q.w)) + a.y * (2 * (q.j * q.k + q.i
				* q.w)) + a.z * (1 - 2 * (pow(q.i, 2) + pow(q.j, 2)));
	return (b);
}
