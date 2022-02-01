NAME		= miniRT

FOLDER		= ./

SRC			= \
change_resolution_bonus.c \
close_game_bonus.c \
colour.c \
create_window_bonus.c \
eni_bonus.c \
ft_exit.c \
ft_nn_bonus.c \
ft_strf_bonus.c \
hud_bonus.c \
key_hook_bonus.c \
main_bonus.c \
math.c \
minirt_bonus.c \
move_bonus.c \
my_mlx_pixel_put_bonus.c \
new_image_bonus.c \
next_level_bonus.c \
prepare_imgs_bonus.c \
render_next_frame_bonus.c \
restart_window_bonus.c \
vector3.c \

HDR			= \
minirt_bonus.h \

SRCS		= $(addprefix $(FOLDER), $(SRC))

HDRS		= $(addprefix $(FOLDER), $(HDR))

OBJS		= $(SRCS:%.c=%.o)

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

MLX			= libmlx.dylib
MLX_PATH	= ../mlx_beta2020/
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
