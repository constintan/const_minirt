NAME		= miniRT
FOLDER		= src/
SRC			= \
ambient.c \
camera.c \
close_minirt.c \
color.c \
color_utils.c \
cone.c \
cylinder.c \
cylinder_raytrace.c \
draw.c \
error_managment.c \
ft_atox.c \
ft_exit.c \
hud.c \
kd_strf.c \
key_hook.c \
libft.c \
libft2.c \
light.c \
minirt.c \
mouse_hook.c \
parse_utils.c \
plane.c \
quaternion.c \
render_next_frame.c \
scene_init.c \
sphere.c \
toggle.c \
vector3.c \

SRC_BON		= \

HDR			= \
minirt.h \

HDR_BON		= \
minirt_bonus.h \

OBJS		= $(addprefix $(FOLDER), $(SRC:%.c=%.o))
OBJS_BON	= $(addprefix $(FOLDER), $(SRC:%.c=%_bonus.o))
HDRS		= $(addprefix $(FOLDER), $(HDR))
HDRS_BON	= $(addprefix $(FOLDER), $(HDR_BON))

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

RM      	= rm -f

MLX			= libmlx.a
MLX_PATH	= mlx_static/
MLX_FLAGS	= -framework OpenGL -framework AppKit

LIBKD		= libft.a
LIBKD_PATH	= libkd/

GNL			= libgnl.a
GNL_PATH	= gnl/

%.o:		%.c $(HDRS)
			$(CC) $(CFLAGS) $(BONUS) -c $< -o $@

%_bonus.o:	%.c $(HDRS) $(HDRS_BON)
			$(CC) $(CFLAGS) -D BONUS=1 -c $< -o $@

all:		mlx libkd gnl $(NAME)

bonus:		mlx libkd gnl .bonus

mlx:
			@echo "Making $(MLX_PATH)$(MLX)"
			@make -C $(MLX_PATH)

libkd:
			@echo "Making $(LIBKD_PATH)$(LIBKD)"
			@make -C $(LIBKD_PATH)

gnl:
			@echo "Making $(GNL_PATH)$(GNL)"
			@make -C $(GNL_PATH)

$(NAME):	$(OBJS) $(MLX_PATH)$(MLX) $(LIBKD_PATH)$(LIBKD) $(GNL_PATH)$(GNL)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_PATH)$(MLX) $(MLX_FLAGS) $(LIBKD_PATH)$(LIBKD) $(GNL_PATH)$(GNL)
			@$(RM) .bonus

.bonus:		$(OBJS_BON) $(MLX_PATH)$(MLX) $(LIBKD_PATH)$(LIBKD) $(GNL_PATH)$(GNL)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS_BON) $(MLX_PATH)$(MLX) $(MLX_FLAGS) $(LIBKD_PATH)$(LIBKD) $(GNL_PATH)$(GNL)
			@touch .bonus

clean:
			@$(RM) $(OBJS) $(OBJS_BON)
			@echo "clean is finished"

mlx_clean:
			@make clean -C $(MLX_PATH) > /dev/null
			@echo "mlx_clean is finished"

libkd_clean:
			@make clean -C $(LIBKD_PATH) > /dev/null
			@echo "libkd_clean is finished"

gnl_clean:
			@make clean -C $(GNL_PATH) > /dev/null
			@echo "gnl_clean is finished"

clean_all:	mlx_clean libkd_clean gnl_clean clean

fclean:
			@$(RM) $(OBJS) $(OBJS_BON) $(NAME) .bonus
			@echo "fclean is finished"

libkd_fclean:
			@make fclean -C $(LIBKD_PATH) > /dev/null
			@echo "libkd_fclean is finished"

gnl_fclean:
			@make fclean -C $(GNL_PATH) > /dev/null
			@echo "gnl_fclean is finished"

fclean_all:	mlx_clean libkd_fclean gnl_fclean fclean

re:			fclean all

re_all:		fclean_all all

norm:
			@make norm -C $(LIBKD_PATH)
			@norminette

leaks:
			leaks --atExit -- ./$(NAME)

.PHONY:		\
all \
bonus \
mlx \
libkd \
gnl \
clean \
mlx_clean \
libkd_clean \
gnl_clean \
clean_all \
fclean \
libkd_fclean \
gnl_fclean \
fclean_all \
re \
re_all \
norm \
leaks \
