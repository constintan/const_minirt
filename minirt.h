/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:18:39 by lajudy            #+#    #+#             */
/*   Updated: 2022/01/30 01:09:35 by lajudy           ###   ########.fr       */
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
# define DEFAULT_BG_COLOR 255, 255, 255


typedef struct	s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct	s_sphere
{
	t_vector		*center;
	double			radius;
	t_color			*color;
	struct s_sphere	*next;
}	t_sphere;

typedef struct	s_plane
{
	t_vector		*position;
	t_vector		*orient;
	t_color			*color;
	struct s_plane	*next;
}	t_plane;

typedef struct	s_cylinder
{
	t_vector		*position;
	t_vector		*orient;
	double			radius;
	double			height;
	t_color			*color;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct	s_camera
{
	t_vector	*origin;
	t_vector	*direction;
	double		fov;
}	t_camera;

typedef struct	s_light
{
	t_vector	*position;
	double		bright;
	t_color		*color;
	//next === доделать!!!!!!!!!!
}	t_light;

typedef struct	s_ambient
{
	double	bright;
	t_color	*color;
}	t_ambient;

typedef struct	s_scene
{
	t_camera	*camera;
	t_ambient	*ambient;
	t_light		*light;

	void	*mlx;
	void	*window;
	void	*img;

	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		bytes_per_line;
	int		endian;

	double		width;
	double		height;

	t_sphere *spheres;
	t_plane *planes;
	t_cylinder *cylinders;

}	t_scene;

// typedef struct	s_shapes
// {
// 	int type;
// 	void *params;
// 	struct s_shapes next;
// }
// доделать!!!!!!!!!!

typedef struct	s_screen
{
	double	width;
	double	height;
	double	x_step;
	double	y_step;
}	t_screen;


//libft.c
size_t			ft_strlen(const char *s);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			free_after_split(char **argv);
int				ft_strcmp(char *s1, char *s2);

//libft2.c
int				ft_isspace(char c);
int				ft_isdigit(int c);
void			check_endline(char **str, int *err);


//error_managment.c
void			ft_error(int er);
int 			invalid_filename(char *filename);

//vector.c
t_vector		*new_vector_atof(char **str, int *err);
t_vector		*new_vector(double x, double y, double z);
t_vector		*vec_subtract(t_vector *vec1, t_vector *vec2);
double			vec_length(t_vector	*vec);
void			vec_normalize(t_vector *vec);
double			vec_dot_product(t_vector *v1, t_vector *v2);


//sphere.c
void			add_sphere(t_scene *scene, char *str);
t_sphere		*new_sphere(t_vector *center, double radius, t_color *color);
int				sphere_intersect(t_camera *camera, t_vector *ray, t_sphere *sphere);

//plane.c
void			add_plane(t_scene *scene, char *str);
t_plane			*new_plane(t_vector *position, t_vector *orient, t_color *color);

//cylinder.c
t_cylinder		*new_cylinder(t_vector *position, t_vector *orient, double radius, double height, t_color *color);
void			add_cylinder(t_scene *scene, char *str);

//camera.c
t_camera		*new_camera(t_vector *origin, t_vector *direction, double fov);
void			add_camera(t_scene *scene, char *str);
void			check_direction_limits(t_vector *direction, int *err);

//ambient.c
t_ambient		*new_ambient(double bright, t_color *color);
void			add_ambient(t_scene *scene, char *str);
void			check_ratio_limits(double bright, int *err);

//light.c
t_light			*new_light(t_vector *position, double bright, t_color *color);
void			add_light(t_scene *scene, char *str);

//scene.c
t_scene			*new_scene(void);

//scene_init.c
t_scene			*scene_init(char *filename);

//ray_tracing.c
t_screen		*new_screen(double width, double height, double fov);
void			ray_tracing(t_scene *scene);

//draw.c
void			draw_pixel(t_scene *sceme, int x, int y, t_color *color);

//get_next_line.c
char			*get_next_line(int fd);

//ft_split.c
char			**ft_split(char const *s, char c);

//ft_atox.c
double			ft_atof(char **str, int *err);
unsigned char	ft_atoc(char **str, int *err);


//color.c
t_color			*new_color(unsigned char r, unsigned char g, unsigned char b);
t_color			*new_color_atoc(char **str, int *err);




#endif