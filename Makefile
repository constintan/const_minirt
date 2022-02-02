NAME		= miniRT

NAME_BONUS	= miniRT

FOLDER		= src/

FOLDER_BON	= src_bonus/

MLX			= libmlx.a
MLX_PATH	= mlx_static/

LIBKD		= libft.a
LIBKD_PATH	= libkd/

GNL			= libgnl.a
GNL_PATH	= gnl/

RM      	= rm -f

all:		mlx libkd gnl $(NAME)

mlx:
			@echo "Making $(MLX_PATH)$(MLX)"
			@make -C $(MLX_PATH)
			@cp $(MLX_PATH)$(MLX) ./

libkd:
			@echo "Making $(LIBKD_PATH)$(LIBKD)"
			@make -C $(LIBKD_PATH)

gnl:
			@echo "Making $(GNL_PATH)$(GNL)"
			@make -C $(GNL_PATH)

$(NAME):
			@make -C $(FOLDER)
			@cp $(FOLDER)$(NAME) ./

bonus:		mlx libkd gnl
			@make -C $(FOLDER_BON)
			@cp $(FOLDER_BON)$(NAME_BONUS) ./

clean:
			@make clean -C $(FOLDER) > /dev/null
			@make clean -C $(FOLDER_BON) > /dev/null
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
			@make fclean -C $(FOLDER) > /dev/null
			@make fclean -C $(FOLDER_BON) > /dev/null
			@$(RM) $(NAME) $(NAME_BONUS) $(MLX)
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
			@make norm -C $(FOLDER)
			@make norm -C $(FOLDER_BON)

leaks:
			leaks --atExit -- ./$(NAME)

.PHONY:		\
all \
$(NAME) \
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
