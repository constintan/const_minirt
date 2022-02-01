/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:43:53 by lajudy            #+#    #+#             */
/*   Updated: 2022/01/29 01:03:28 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
	
	// t_vector	*sphere_center = new_vector(3, 2, -32);
	// t_sphere	*sphere = new_sphere(sphere_center, 6);

int	main(int argc, char **argv)
{
	t_scene *scene;
	// t_vector	*camera_origin = new_vector(0, 0, 0);
	// t_vector	*camera_direction = new_vector(0, 0, -1);
	// t_camera	*camera = new_camera(camera_origin, camera_direction, 20);

	if (argc == 1 || invalid_filename(argv[1]))
		ft_error(1);
	scene = scene_init(argv[1]);
	// scene->camera = camera;

	ray_tracing(scene);
	mlx_loop(scene->mlx);
}
