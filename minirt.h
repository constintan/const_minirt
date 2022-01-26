/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:18:39 by lajudy            #+#    #+#             */
/*   Updated: 2022/01/27 01:27:33 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "gnl/get_next_line.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define WINDOW_NAME "miniRT window"

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct	s_sphere
{
	t_vector	*center;
	float		radius;
}	t_sphere;

typedef struct	s_camera
{
	t_vector	*origin;
	t_vector	*direction;
	float		fov;
}	t_camera;

typedef struct	s_scene
{
	t_camera	*camera;
	t_sphere	*sphere;
	float		width;
	float		height;
}	t_scene;

typedef struct	s_screen
{
	float	width;
	float	height;
	float	x_step;
	float	y_step;
}	t_screen;


//libft.c
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);

//error_managment.c
void		ft_error(int er);

//vector.c
t_vector	*new_vector(float x, float y, float z);
t_vector	*vec_subtract(t_vector *vec1, t_vector *vec2);
float		vec_length(t_vector	*vec);
void		vec_normalize(t_vector *vec);
float		vec_dot_product(t_vector *v1, t_vector *v2);

//sphere.c
t_sphere	*new_sphere(t_vector *center, float radius);
int			sphere_intersect(t_camera *camera, t_vector *ray, t_sphere *sphere);

//camera.c
t_camera	*new_camera(t_vector *origin, t_vector *direction, float fov); 

//scene.c
t_scene		*new_scene(t_camera *camera, t_sphere *sphere);

//ray_tracing.c
t_screen	*new_screen(float width, float height, float fov);
void		ray_tracing(void *mlx, void *window, t_scene *scene);


#endif