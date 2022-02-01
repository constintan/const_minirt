/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 16:59:35 by swilmer           #+#    #+#             */
/*   Updated: 2022/01/30 23:15:36 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	main(int argc, char const **argv)
{
//	double	theta;
//	double	x1;
//	double	y1;
//	double	x2;
//	double	y2;
//	double	width;
//	t_vector3 	dir;
//
//	x1 = 1;
//	y1 = 0;
//	theta = M_PI / 180 * 70;
//	x2 = x1 * cos(theta) - y1 * sin(theta);
//	y2 = x1 * sin(theta) + y1 * cos(theta);
//	width = 2 * tan(theta / 2 * (M_PI / 180));
//	dir.x = width * 16;
//	dir.y = 1;
//	dir.z = 0;
//	dir = vector3_normalise(dir);
//	printf("x2 %f, y2 %f\nx3 %f, y3 %f\n", x2, y2, dir.x, dir.y);
//	exit(0);
	if (argc == 1)
		kd_exit("Error\nPass [map].rt as an argument and check README.md\n");
	minirt(&argv[1]);
	kd_free_all();
	return (0);
}
