/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libkd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 21:02:21 by swilmer           #+#    #+#             */
/*   Updated: 2022/01/27 15:42:06 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBKD_H
# define LIBKD_H
//# define ft kd
# include "added/ft_malloc/ft_malloc.h" //malloc, free //ENOMEM //write
# include <unistd.h> //write
# include <stdlib.h> //malloc, free
# include <limits.h> //INT_MIN, INT_MAX
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int				kd_strcmpi(char const *s1, char const *s2);
void			kd_striteri(char *s, void (*f)(unsigned int, char*));

void			*kd_free_array(void **array, int size);
char			*kd_gnl(int fd);
void			kd_lstadd_back(t_list **lst, t_list *new);
void			kd_lstclear(t_list **lst, void (*del)(void *));
int				kd_putstr_fd(char *s, int fd);
char			**kd_split(char const *str, char c);
char			*kd_strdup(char const *s1);
char			*kd_strjoin(char const *s1, char const *s2);
char			*kd_strjoin_free(char *s1, char *s2, int option);
char			*kd_strmapi(char const *s, char (*f)(unsigned int, char));
char			*kd_strtrim(char const *src, char const *set);
char			*kd_substr(char const *src, unsigned int start, size_t len);

unsigned int	kd_abs(int n);
int				*kd_arrbbl(int *array, int count);
int				*kd_arrdup(int *array, int count);
int				kd_arrissrt(int *array, int count);
int				kd_arrisunq(int *array, int count);
int				kd_atoi(const char *str);
void			kd_bzero(void *s, size_t n);
void			*kd_calloc(size_t count, size_t size);
int				kd_count_strings(char **strings);
void			*kd_free_strings(char **strings);
int				kd_isalnum(int c);
int				kd_isalpha(int c);
int				kd_isascii(int c);
int				kd_isdigit(int c);
int				kd_islower(int c);
int				kd_isprint(int c);
int				kd_isspace(int c);
int				kd_isupper(int c);
char			*kd_itoa(int n);
void			kd_lstadd_front(t_list **lst, t_list *new);
void			kd_lstdelone(t_list *lst, void (*del)(void *));
t_list			*kd_lstfind(t_list *lst, void *find, int (*f)(void *, void *));
void			kd_lstiter(t_list *lst, void (*f)(void *));
t_list			*kd_lstlast(t_list *lst);
t_list			*kd_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
t_list			*kd_lstnew(void *content);
void			kd_lstremove(t_list **lst, t_list *remove, void (*del)(void *));
int				kd_lstsize(t_list *lst);
int				kd_max(int a, int b);
void			*kd_memccpy(void *dst, const void *restrict src,
					int c, size_t n);
void			*kd_memchr(const void *s, int c, size_t n);
int				kd_memcmp(const void *s1, const void *s2, size_t n);
void			*kd_memcpy(void *dst, const void *src, size_t n);
void			*kd_memmove(void *dst, const void *src, size_t len);
void			*kd_memset(void *b, int c, size_t len);
int				kd_min(int a, int b);
int				kd_nbrlen_uint(unsigned int n);
int				kd_nbrlen(int n);
int				kd_ptrcmp(void *p1, void *p2);
int				kd_putchar_fd(char c, int fd);
int				kd_putchar(char c);
int				kd_putendl_fd(char *s, int fd);
int				kd_putendl(char *s);
int				kd_putnbr_fd(int n, int fd);
int				kd_putnbr(int n);
int				kd_putstr(char *s);
int				kd_satoi(char const *str, int *n);
char			*kd_stpcpy(char *dest, char const *src);
char			*kd_strcat(char *dest, char const *src);
char			*kd_strchr(const char *s, int c);
int				kd_strcmp(char const *s1, char const *s2);
char			*kd_strcpy(char *dest, char const *src);
char			*kd_strimplode(char **strs, char *sep);
size_t			kd_strlcat(char *dst, const char *src, size_t size);
size_t			kd_strlcpy(char *dst, char const *src, size_t dstsize);
size_t			kd_strlen(const char *str);
int				kd_strncmp(const char *s1, const char *s2, size_t n);
size_t			kd_strnlen(char const *str, size_t maxlen);
char			*kd_strnstr(const char *big, const char *little,
					size_t len);
char			*kd_strrchr(const char *s, int c);
char			*kd_strrev(char *str);
char			*kd_substring(char const *src, unsigned int start,
					unsigned int end);
int				kd_tolower(int c);
int				kd_toupper(int c);

#endif //LIBKD_H
