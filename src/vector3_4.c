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
	double	tmp;

	tmp = a.x;
	a.x = a.y;
	a.y = a.z;
	a.z = tmp;
	return (a);
}

t_vector3	vector3_ccw(t_vector3 a)
{
	double	tmp;

	tmp = a.z;
	a.z = a.y;
	a.y = a.x;
	a.x = tmp;
	return (a);
}
