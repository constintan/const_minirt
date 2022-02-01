/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/01 15:44:28 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H
# include "../libkd/libkd.h"
# include <fcntl.h>
# include "../mlx_beta2020/mlx.h"
# include <math.h>

# include <stdio.h> //printf

# include <pthread.h>

# define EPSILON 1e-6

# define IMG 100

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

typedef struct s_xy
{
	int	x;
	int	y;
}	t_xy;

enum e_keycode
{
	KEY_W = 13,
	KEY_S = 1,
	KEY_A = 0,
	KEY_D = 2,
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
	KEY_ENTER = 36,
	KEY_TAB = 48
}	t_keycode;

typedef struct s_img {
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_vector2
{
	double		u;
	double		v;
}	t_vector2;

typedef struct s_vector3
{
	double		x;
	double		y;
	double		z;
}	t_vector3;

typedef enum e_objtype
{
	NO_OBJTYPE,
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	HYPERBOLOID,
	PARABOLOID
}	t_objtype;

typedef struct s_obj
{
	t_objtype		type;
	t_color			colour;
	t_vector3		position;
	t_vector3		orientation;
	double			diameter;
	double			radius;
	double			height;
	double			max_distance;
	void			*texture;
	void			*bump;
	struct s_obj	*next;
}	t_obj;

typedef struct s_camera
{
	t_vector3		position;
	t_vector3		orient;
	t_vector2		rotate;
	double			fov;
	double			zoom;
}	t_camera;

typedef struct s_ambient
{
	double			bright;
	t_color			color;
}	t_ambient;

typedef struct s_light
{
	t_vector3		position;
	double			bright;
	t_color			color;
	struct s_light	*next;
}	t_light;

typedef struct s_ray
{
	t_vector3	position;
	t_vector3	orientation;
	t_obj		*obj;
	double		t;
	double		distance;
	t_vector3	coordinates;
	t_vector3	normal;
	t_color		color;
}	t_ray;
//quadratic function, d - discriminant
typedef struct s_quad {
	double		a;
	double		b;
	double		c;
	double		d;
}	t_quad;

typedef struct s_mlx {
	void		*init;
	void		*win;
	t_img		*bgr_img;
	t_img		*shade;
	int			w;
	int			h;
	char		*hud;
	int			hud_flash;
	int			width;
	int			height;
	const char	**maps;
	int			map_index;
	t_obj		*obj;
	t_camera	*camera;
	t_ambient	*ambient;
	t_light		*light;
	t_img		*sim;
	t_bool		play;
	int			view;
}	t_mlx;

typedef struct s_thread {
	pthread	thread;
	int		index;
	t_mlx	*mlx;
}	t_thread;

typedef struct s_countchars
{
	int	c;
	int	e;
	int	p;
}	t_countchars;

void	minirt(const char **map);
void	*kd_nn(void *ptr, char *msg);
void	create_window(t_mlx *mlx);
t_img	*new_image(t_mlx *mlx, int w, int h);
void	fill_square_img(t_img *img, int width, int height, unsigned int colour);
void	my_mlx_pixel_put(t_img *img, int x, int y, int colour);
void	fill_circle_gradient_img(t_img *img, int radius, unsigned int colour1,
			unsigned int colour2);
int		close_game(void);
void	parse_map(const char *map, t_mlx *mlx);
void	parse_map_ber_ext(const char *map);
int		parse_map_line_count(const char *map);
char	**parse_map_get_strings(const char *map, int lines);
int		parse_map_line_len(char **s);
void	parse_map_check_walls(char **ss, int len, int lines);
void	parse_map_check_chars(char **ss);
//t_box	**parse_map_create_boxes(char **ss, int len, int lines, t_mlx *mlx);
void	parse_map_connect_boxes(int len, int lines, t_mlx *mlx);
int		parse_map_open_file(const char *map);
void	prepare_imgs(t_mlx *mlx);
void	prepare_settings(t_mlx *mlx);
int		render_next_frame(t_mlx *mlx);
int		key_hook(int key, t_mlx *mlx);
char	*kd_strf(char const *format, ...);
void	*eni(void *ptr);
void	render_map(t_mlx *mlx);
void	render_hero(t_mlx *mlx);
int		calc_hmove_x(t_mlx *mlx);
int		calc_hmove_y(t_mlx *mlx);
int		move(t_mlx *mlx);
void	hud(t_mlx *mlx);
void	change_resolution(int key, t_mlx *mlx);
void	reset_game(t_mlx *mlx);
//void	render_box(t_box box, int x, int y, t_mlx *mlx);
void	next_level(t_mlx *mlx);
void	restart_window(t_mlx *mlx);
int		calc_move_x(int x, t_mlx *mlx);
int		calc_move_y(int y, t_mlx *mlx);
void		kd_exit(char *s);

void	*thread_loop(void *mlx_void);
//vector3
t_vector3	matrix3_subtract(t_vector3 a, t_vector3 b);
t_vector3	matrix3_addition(t_vector3 a, t_vector3 b);
double		vector3_distance(t_vector3 a, t_vector3 b);
t_vector3	vector3_normalise(t_vector3 direction);
t_vector3	vector3_multiply(t_vector3 direction, double multiply);
double		vector3_sumpow2(t_vector3 a);
double		vector3_scalar(t_vector3 a, t_vector3 b);
t_vector3	vector3_rotate(t_vector3 a, t_vector2 rotate);
t_vector3	new_vector3(double x, double y, double z);
t_vector2	new_vector2(double u, double v);
t_vector3	vector3_negate(t_vector3 a);
//math
double		math_discriminant(double a, double b, double c);
//colour
unsigned int	colour_rgb2hex(t_color colour);
t_color		colour_amplify(t_color colour, double amplifier);
t_color		colour_add(t_color colour1, t_color colour_add);
t_color		colour_clamp(t_color colour);
t_color		colour_matrix_amplify(t_color colour, t_color colour_amplifier);

#endif //MINIRT_BONUS_H
