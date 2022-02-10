NAME		= miniRT

FOLDER		= ./

SRC			= \
minirt.c \
render_next_frame.c \
kd_strf.c \
vector3.c \
hud.c \
ambient.c \
camera.c \
color.c \
cylinder.c \
cylinder_raytrace.c \
draw.c \
error_managment.c \
ft_atox.c \
libft.c \
libft2.c \
light.c \
plane.c \
quaternion.c \
scene_init.c \
sphere.c \
parse_utils.c \
cone.c \

HDR			= \
minirt.h \

SRCS		= $(addprefix $(FOLDER), $(SRC))

HDRS		= $(addprefix $(FOLDER), $(HDR))

OBJS		= $(SRCS:%.c=%.o)

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

MLX			= libmlx.a
MLX_PATH	= ../mlx_static/
MLX_FLAGS	= -framework OpenGL -framework AppKit

LIBKD		= libft.a
LIBKD_PATH	= ../libkd/

GNL			= libgnl.a
GNL_PATH	= ../gnl/

RM      	= rm -f

%.o:		%.c $(HDRS)
			$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

bonus:		all

$(NAME):	$(OBJS) $(MLX_PATH)$(MLX) $(LIBKD_PATH)$(LIBKD) $(GNL_PATH)$(GNL)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_PATH)$(MLX) $(MLX_FLAGS) $(LIBKD_PATH)$(LIBKD) $(GNL_PATH)$(GNL)
			@cp $(MLX_PATH)$(MLX) ./

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME) $(MLX)

re:			fclean all

norm:
			@norminette

.PHONY:		all bonus clean fclean re norm
