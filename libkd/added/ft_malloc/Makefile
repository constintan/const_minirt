NAME		= libft_malloc.a

SRCS		= \
ft_free.c \
ft_malloc.c \
ft_malloc_debug.c \
ft_malloc_lst.c \
ft_malloc_queue.c \

OBJS		= $(SRCS:%.c=%.o)

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

RM      	= rm -f

%.o:		%.c Makefile ft_malloc.h
			$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			$(RM) $(NAME)
			ar rcs $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
