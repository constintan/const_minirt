/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: konstanting <konstanting@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:18:39 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/12 16:02:37 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../mlx_static/mlx.h"
# include "../gnl/get_next_line.h"
# include "../libkd/libkd.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

# ifndef BONUS
#  define BONUS 0
# endif

# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 1200
# define WN "miniRT window"
# define DEF_BG_COLOR_R 128
# define DEF_BG_COLOR_G 128
# define DEF_BG_COLOR_B 128
# define DEFAULT_ZOOM 32
# define EPSILON 1e-6

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

enum e_keycode
{
	KEY_W = 13,
	KEY_S = 1,
	KEY_A = 0,
	KEY_D = 2,
	KEY_Q = 12,
	KEY_E = 14,
	KEY_Z = 6,
	KEY_X = 7,
	KEY_C = 8,
	KEY_V = 9,
	KEY_B = 11,
	KEY_N = 45,
	KEY_M = 46,
	KEY_F = 3,
	KEY_I = 34,
	KEY_J = 38,
	KEY_K = 40,
	KEY_L = 37,
	KEY_U = 32,
	KEY_O = 31,
	KEY_CMD = 259,
	KEY_SHIFT = 257,
	KEY_SPACE = 49,
	KEY_UP = 126,
	KEY_DOWN = 125,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_R = 15,
	KEY_ESC = 53,
	KEY_1 = 18,
	KEY_2 = 19,
	KEY_3 = 20,
	KEY_4 = 21,
	KEY_5 = 23,
	KEY_6 = 22,
	KEY_7 = 26,
	KEY_8 = 28,
	KEY_9 = 25,
	KEY_0 = 29,
	KEY_ENTER = 36,
	KEY_TAB = 48,
	KEY_OPENBRACKET = 33,
	KEY_CLOSEBRACKET = 30
}	t_keycode;

typedef struct s_vector2
{
	double		u;
	double		v;
}	t_vector2;

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}	t_vector3;

typedef struct s_quaternion
{
	double	w;
	double	i;
	double	j;
	double	k;
}	t_quaternion;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_camera
{
	t_vector3		position;
	t_vector3		orient;
	t_vector2		rotate;
	t_vector3		rotate_origin;
	double			fov;
	double			zoom;
	struct s_camera	*defaults;
}	t_camera;

typedef struct s_ambient
{
	double	bright;
	t_color	color;
}	t_ambient;

typedef struct s_light
{
	t_vector3		position;
	double			bright;
	t_color			color;
	struct s_light	*next;
}	t_light;

typedef struct s_plane
{
	t_vector3		position;
	t_vector3		orient;
	t_color			color;
	struct s_plane	*next;
}	t_plane;

typedef struct s_disc
{
	t_vector3		position;
	t_vector3		orient;
	double			radius;
	t_color			color;
	struct s_plane	*next;
}	t_disc;

typedef struct s_sphere
{
	t_vector3		position;
	double			radius;
	t_color			color;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_cylinder
{
	t_vector3			position;
	t_vector3			orient;
	double				radius;
	double				height;
	t_disc				cap_bot;
	t_disc				cap_top;
	t_color				color;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_cone
{
	t_vector3		position;
	t_vector3		orient;
	double			radius;
	double			height;
	t_color			color;
	t_disc			cap;
	double			theta;
	double			costheta;
	double			pow2costheta;
	struct s_cone	*next;
}	t_cone;

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
	char	*addr;
	int		bits_per_pixel;
	int		bytes_per_line;
	int		endian;
}	t_img;

typedef struct s_ray
{
	t_vector3	position;
	t_vector3	orient;
	double		t;
	t_vector3	coordinates;
	t_vector3	normal;
	t_color		color;
}	t_ray;

typedef struct s_scene
{
	t_camera	*camera;
	t_ambient	*ambient;
	t_light		*light;
	t_light		*current_light;
	t_plane		*planes;
	t_sphere	*spheres;
	t_cylinder	*cylinders;
	t_cone		*cones;
	int			width;
	int			height;
	void		*mlx;
	void		*window;
	t_img		*img;
	t_img		*img2;
	char		*hud;
	t_bool		no_shadows;
	t_bool		one_light;
	t_bool		no_lights;
	t_bool		no_specular;
	t_bool		checkerboard;
	t_bool		bump;
	t_bool		gamma_correction;
	int			oddframe;
	int			maxquality;
	int			minquality;
	int			everynframe;
	int			play;
	int			idle;
	int			view;
	double		gamma;
	t_ray		*rays;
	t_bool		rays_set;
	t_img		*bumpmap;
	t_img		*texturemap;
	char		**maps;
	int			map_index;
	void		*bonus;
}	t_scene;

//quadratic equation, d - discriminant, t1 t2 - roots
typedef struct s_quad {
	double		a;
	double		b;
	double		c;
	double		d;
	double		sqrt_d;
	double		t1;
	double		t2;
}	t_quad;

typedef struct s_cl {
	t_light		*light;
	t_vector3	l;
	double		fctr;
	t_color		color;
	double		hf;
	t_vector3	h;
	double		n;
}	t_cl;

typedef struct s_pl {
	char		*dst;
	t_vector3	local;
	t_vector3	ulocal;
	double		costheta;
	t_vector2	tile;
	t_vector3	color;
}	t_pl;

//libft.c
size_t			ft_strlen(const char *s);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);

//libft2.c
int				ft_isspace(char c);
int				ft_isdigit(int c);
void			check_endline(char **str, int *err);

//error_managment.c
void			ft_error(int er);
int				invalid_filename(char *filename);

//parse_utils.c
t_vector3		new_vector_atof(char **str, int *err);

//sphere.c
void			intersect_sphere(t_sphere *sphere, t_ray *r, t_scene *scene);
void			add_sphere(t_scene *scene, char *str);
t_sphere		*new_sphere(t_vector3 position, double radius, t_color color);

//plane.c
void			add_plane(t_scene *scene, char *str);
t_plane			*new_plane(t_vector3 position, t_vector3 orient, t_color color);
void			texture_plane(t_plane *plane, t_ray *ray, t_bool bump,
					t_scene *scene);

//cylinder.c
t_cylinder		*new_cylinder(t_vector3 position, t_vector3 orient,
					double radius);
void			add_cylinder_props(t_cylinder *cylinder, char *str);
void			add_cylinder(t_scene *scene, char *str);

//cylinder_raytrace.c
int				is_in_cutted_cylinder(t_cylinder *cylinder, t_ray *ray,
					t_quad q);
void			init_cylinder_q(t_cylinder *cylinder, t_ray	*ray, t_quad *q);
void			intersect_cylinder(t_cylinder *cylinder, t_ray *ray,
					t_scene *scene);

//camera.c
t_camera		*new_camera(t_vector3 position, t_vector3 orient, double fov);
void			add_camera(t_scene *scene, char *str);
void			check_direction_limits(t_vector3 orient, int *err);
void			reset_camera(t_scene *scene);

//ambient.c
t_ambient		*new_ambient(double bright, t_color color);
void			add_ambient(t_scene *scene, char *str);
void			check_ratio_limits(double bright, int *err);

//light.c
t_light			*new_light(t_vector3 position, double bright, t_color color);
void			add_light(t_scene *scene, char *str);

//scene_init.c
void			mlx_window_init(t_scene *scene);
void			scene_init(char *filename, t_scene *scene);

//draw.c
void			draw_pixel(t_scene *scene, int x, int y, t_color color);

//get_next_line.c
char			*get_next_line(int fd);

//ft_atox.c
double			ft_atof(char **str, int *err);
unsigned char	ft_atoc(char **str, int *err);

//color.c
t_color			new_color(int r, int g, int b);
t_color			new_color_atoc(char **str, int *err);
t_color			new_light_color_atoc(char **str, int *err);

t_color			colour_amplify(t_color colour, double amplifier);
t_color			colour_add(t_color colour1, t_color colour_add);
t_color			colour_clamp(t_color colour);
t_color			colour_matrix_amplify(t_color colour, t_color colour_amplifier);
t_color			colour_gamma_collect(t_color colour, t_scene *scene);
t_color			colour_gamma_apply(t_color colour, t_scene *scene);

//cone.c
void			intersect_cone(t_cone *cone, t_ray *ray, t_scene *scene);
t_cone			*new_cone(t_vector3 position, t_vector3 orient, double radius);
void			add_cone_props(t_cone *cone, char *str);
void			add_cone(t_scene *scene, char *str);

//render_next_frame.c
int				render_next_frame(t_scene *scene);
void			intersect_plane(t_plane *plane, t_ray *ray, t_bool bump,
					t_scene *scene);
void			intersect_disc(t_disc *disc, t_ray *ray, t_scene *scene);
double			math_quadratic_equation(t_quad *q);
//hud.c
void			hud(t_scene *scene);

//vector3.c
t_vector3		matrix3_subtract(t_vector3 a, t_vector3 b);
t_vector3		matrix3_addition(t_vector3 a, t_vector3 b);
double			vector3_distance(t_vector3 a, t_vector3 b);
t_vector3		vector3_normalise(t_vector3 direction);
t_vector3		vector3_multiply(t_vector3 direction, double multiply);
double			vector3_sumpow2(t_vector3 a);
double			vector3_scalar(t_vector3 a, t_vector3 b);
t_vector3		vector3_qrotate(t_vector3 a, double theta, t_vector3 axis);
t_vector3		vector3_rotate_yx(t_vector3 a, t_vector2 rotate);
t_vector3		vector3_rotate_xy(t_vector3 b, t_vector2 rotate);
t_vector2		vector3_arotate(t_vector3 a, t_vector3 b);
t_vector3		new_vector3(double x, double y, double z);
t_vector2		new_vector2(double u, double v);
t_vector3		vector3_negate(t_vector3 a);
t_vector3		vector3_cw(t_vector3 a);
t_vector3		vector3_ccw(t_vector3 a);

//quaternion.c
double			quaternion_sumpow2(t_quaternion q);
t_quaternion	quaternion_normalise(t_quaternion q);
t_quaternion	new_quaternion(double theta, t_vector3 axis);

void			intersect(t_ray *ray, t_scene *scene);
void			raytrace(int x, int y, t_ray *ray, t_scene *scene);
//ft_exit.c
void			ft_exit(int status);
//close_minirt.c
int				close_minirt(void);
//toggle.c
t_bool			toggle(t_bool *b);
//key_hook.c
int				key_hook(int key, t_scene *scene);
//mouse_hook.c
int				mouse_hook(int button, int x, int y, t_scene *scene);
//new_image.c
t_img			*new_image(char *path, int width, int height, t_scene *scene);
//key_hook.c
int				move_light(int key, t_scene *scene);
int				toggle_flags(int key, t_scene *scene);
int				change_minquality(int key, t_scene *scene);
int				change_maxquality(int key, t_scene *scene);
int				move_camera(int key, t_scene *scene);
int				change_fov(int key, t_scene *scene);
int				rotate_camera(int key, t_scene *scene);
void			rotate_camera_xz(t_camera *camera, int theta);
void			rotate_camera_y(t_camera *camera, int theta);
void			redraw_frame(t_scene *scene);
void			next_scene(t_scene *scene);
int				close_minirt(void);
//views.c
void			ray_orthographic(t_camera *camera, t_vector2 step, t_ray *ray);
void			ray_perspective_tan(t_camera *camera, t_vector2 step,
					t_ray *ray);
void			ray_perspective_spherise(t_camera *camera, t_vector2 step,
					t_ray *ray);
void			ray_perspective_spherise2(t_camera *camera, t_vector2 step,
					t_ray *ray);
void			ray_perspective_spherise3(t_camera *camera, t_vector2 step,
					t_ray *ray);
void			ray_perspective_quaternion(t_scene *scene, int x, int y,
					t_ray *ray);
void			ray_perspective_quaternion2(t_scene *scene, int x, int y,
					t_ray *ray);

//raytrace.c
void			compute_light(t_ray *ray, t_scene *scene);
void			update_window(t_scene *scene);
void			reset_rays(t_scene *scene);
void			animate(t_scene *scene);
void			iterate_pixels_gamma_correction(t_scene *scene);

#endif