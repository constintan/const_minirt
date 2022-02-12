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

//printf("%f %f\n", vector3_scalar(a, vector3_rotate_yx(b, r)),
// vector3_scalar(a, vector3_rotate_yx(b, c)));
t_vector2	vector3_arotate(t_vector3 a, t_vector3 b)
{
	t_vector2	c;
	t_vector2	r;

	c.u = 0;
	c.v = 0;
	r.v = -90;
	while (r.v <= 90)
	{
		r.u = 0;
		while (r.u < 360)
		{
			if (vector3_scalar(a, vector3_rotate_yx(b, r)) > vector3_scalar(a,
					vector3_rotate_yx(b, c)))
				c = r;
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
