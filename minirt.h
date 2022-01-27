/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:18:39 by lajudy            #+#    #+#             */
/*   Updated: 2022/01/27 23:35:37 by lajudy           ###   ########.fr       */
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
# include <fcntl.h>

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
	t_vector		*center;
	float			radius;
	struct s_sphere	*next;
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

	void	*mlx;
	void	*window;
	void	*img;

	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		bytes_per_line;
	int		endian;

	float		width;
	float		height;

	t_sphere *spheres;

}	t_scene;

typedef struct	s_screen
{
	float	width;
	float	height;
	float	x_step;
	float	y_step;
}	t_screen;


//libft.c
size_t		ft_strlen(const char *s);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		free_after_split(char **argv);
int			ft_strcmp(char *s1, char *s2);

//libft2.c
int	ft_isspace(char c);

//error_managment.c
void		ft_error(int er);
int 		invalid_filename(char *filename);

//vector.c
t_vector	*new_vector(float x, float y, float z);
t_vector	*vec_subtract(t_vector *vec1, t_vector *vec2);
float		vec_length(t_vector	*vec);
void		vec_normalize(t_vector *vec);
float		vec_dot_product(t_vector *v1, t_vector *v2);

//sphere.c
int			add_sphere(t_scene *scene, char *str);
t_sphere	*new_sphere(t_vector *center, float radius);
int			sphere_intersect(t_camera *camera, t_vector *ray, t_sphere *sphere);

//camera.c
t_camera	*new_camera(t_vector *origin, t_vector *direction, float fov); 

//scene.c
t_scene		*new_scene(void);

//scene_init.c
t_scene	*scene_init(char *filename);

//ray_tracing.c
t_screen	*new_screen(float width, float height, float fov);
void		ray_tracing(t_scene *scene);

//draw.c
void	draw_pixel(t_scene *sceme, int x, int y, int color);

//get_next_line.c
char	*get_next_line(int fd);

//ft_split.c
char	**ft_split(char const *s, char c);

#endif