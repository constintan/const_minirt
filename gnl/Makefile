
SRCS = get_next_line.c get_next_line_utils.c
		
OBJS = 	${SRCS:.c=.o}
HDRS = get_next_line.h

CC = 	gcc
CFLAGS = -Wall -Wextra -Werror

RM = 	rm -f
NAME = libgnl.a

gnl:	${NAME}

# $(NAME): Makefile

$(NAME): ${OBJS} 
	ar rcs ${NAME} $?

${OBJS}:${HDRS}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}


re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader ${SRCS}
	norminette -R CheckDefine ${HDRS}

.PHONY: gnl clean fclean re norm