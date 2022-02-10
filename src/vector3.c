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

t_vector3	vector3_multiply(t_vector3 direction, double multiply)
{
	direction.x *= multiply;
	direction.y *= multiply;
	direction.z *= multiply;
	return (direction);
}

double	vector3_sumpow2(t_vector3 a)
{
	return(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
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
	b.x = a.x * (1 - 2 * (pow(q.j, 2) + pow(q.k, 2))) + a.y * (2 * (q.i * q.j - q.k * q.w)) + a.z * (2 * (q.i * q.k + q.j * q.w));
	b.y = a.x * (2 * (q.i * q.j + q.k * q.w)) + a.y * (1 - 2 * (pow(q.i, 2) + pow(q.k, 2))) + a.z * (2 * (q.j * q.k - q.i * q.w));
	b.z = a.x * (2 * (q.i * q.k - q.j * q.w)) + a.y * (2 * (q.j * q.k + q.i * q.w)) + a.z * (1 - 2 * (pow(q.i, 2) + pow(q.j, 2)));
	return (b);
}

t_vector3	vector3_rotate_yx(t_vector3 a, t_vector2 rotate)
{
	t_vector3	b;

	rotate.v = M_PI / 180 * -rotate.v;
	b.x = a.x;
	b.y = a.y * cos(rotate.v) - a.z * sin(rotate.v);
	b.z = a.y * sin(rotate.v) + a.z * cos(rotate.v);
	rotate.u = M_PI / 180 * -rotate.u;
	a.x = b.x * cos(rotate.u) - b.z * sin(rotate.u);
	a.y = b.y;
	a.z = b.x * sin(rotate.u) + b.z * cos(rotate.u);
	return (a);
}

t_vector3	vector3_rotate_xy(t_vector3 b, t_vector2 rotate)
{
	t_vector3	a;

	rotate.u = M_PI / 180 * -rotate.u;
	a.x = b.x * cos(rotate.u) - b.z * sin(rotate.u);
	a.y = b.y;
	a.z = b.x * sin(rotate.u) + b.z * cos(rotate.u);
	rotate.v = M_PI / 180 * -rotate.v;
	b.x = a.x;
	b.y = a.y * cos(rotate.v) - a.z * sin(rotate.v);
	b.z = a.y * sin(rotate.v) + a.z * cos(rotate.v);
	return (b);
}

t_vector2	vector3_arotate(t_vector3 a, t_vector3 b)
{
	t_vector2	c;
	t_vector2	r;

	(void)b;
	c.u = 0;
	c.v = 0;
	r.v = -90;
	while (r.v <= 90)
	{
		r.u = 0;
		while (r.u < 360)
		{
			if (vector3_scalar(a, vector3_rotate_yx(b, r)) > vector3_scalar(a,
																			vector3_rotate_yx(
																				 b,
																				 c)))
			{
//				printf("%f %f\n", vector3_scalar(a, vector3_rotate_yx(b, r)), vector3_scalar(a,
//																							 vector3_rotate_yx(
//																								  b,
//																								  c)));
				c = r;
			}
			r.u++;
		}
		r.v++;
	}
	return (c);
}

t_vector3	new_vector3(double x, double y, double z)
{
	t_vector3	a;

	a.x = x;
	a.y = y;
	a.z = z;
	return (a);
}

t_vector2	new_vector2(double u, double v)
{
	t_vector2	a;

	a.u = u;
	a.v = v;
	return (a);
}

t_vector3	vector3_negate(t_vector3 a)
{
	a.x = -a.x;
	a.y = -a.y;
	a.z = -a.z;
	return (a);
}

t_vector3	vector3_cw(t_vector3 a)
{
	double tmp;

	tmp = a.x;
	a.x = a.y;
	a.y = a.z;
	a.z = tmp;
	return (a);
}

t_vector3	vector3_ccw(t_vector3 a)
{
	double tmp;

	tmp = a.z;
	a.z = a.y;
	a.y = a.x;
	a.x = tmp;
	return (a);
}