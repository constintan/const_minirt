# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/04 17:15:03 by lajudy            #+#    #+#              #
#    Updated: 2022/01/29 19:42:38 by lajudy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	minirt.c  error_managment.c \
		vector.c sphere.c camera.c \
		ray_tracing.c \
		libft.c libft2.c \
		draw.c scene_init.c\
		ft_atox.c color.c ambient.c \
		light.c plane.c cylinder.c



BSRCS = 

HDRS =	minirt.h

PATHTOMLX = minilibx_macos/
PATHTOGNL = gnl/
MLX = ${PATHTOMLX}libmlx.a
GNL = ${PATHTOGNL}libgnl.a

OBJS = 	$(SRCS:.c=.o)

NAME = 	minirt

CC = 	gcc
CFLAGS = -Wall -Wextra -Werror
FRMWRKS = -framework OpenGL -framework AppKit 
RM = 	rm -f

all:	${GNL} ${MLX} ${NAME} 

${GNL}: 
	@echo "Making ${GNL}"
	@make -C ${PATHTOGNL}

${MLX}: 
	@make -C ${PATHTOMLX}


$(OBJS):$(HDRS) Makefile

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L${PATHTOGNL} -lgnl -L${PATHTOMLX} -lmlx  ${FRMWRKS} -o $(NAME)

bonus: all

clean:
	${RM} ${OBJS}
	@make -C ${PATHTOGNL} clean
	@make -C ${PATHTOMLX} clean

fclean: clean
	${RM} ${NAME}
	@make -C ${PATHTOGNL} fclean

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader ${SRCS} ${BSRCS}
	norminette -R CheckDefine ${HDRS}

.PHONY: all clean fclean re bonus norm