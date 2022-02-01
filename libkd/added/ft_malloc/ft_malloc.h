/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:04:07 by swilmer           #+#    #+#             */
/*   Updated: 2022/01/27 01:27:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H
# include <stdlib.h> //malloc, free
# include <errno.h> //ENOMEM
# include <unistd.h> //write

typedef struct s_malloc
{
	char			*tag;
	void			*content;
	struct s_malloc	*next;
}	t_malloc;

//ft_free.c
void		*kd_free(void *p);
void		*kd_free_tag(char const *tag);
int			kd_free_queue(void *p, char const *tag);
int			kd_free_all(void);
//ft_malloc.c
void		*kd_malloc(size_t size);
void		*kd_maltag(size_t size, char const *tag);
void		*kd_malloc_add(void *p);
void		*kd_maltag_add(void *p, char const *tag);
void		*kd_malloc_add_queue(void *p, char const *tag);
//ft_malloc_debug.c
void		kd_malloc_debug(void);
void		kd_maltag_debug(char const *tag);
//ft_malloc_lst.c
void		kd_malloc_lstremove(t_malloc **list, t_malloc *remove);
t_malloc	*kd_malloc_lstfind(t_malloc *lst, void *find);
t_malloc	*kd_maltag_lstfind(t_malloc *lst, char const *tag);
t_malloc	*kd_malloc_lstnew(void *content, char const *tag);
//ft_malloc_queue.c
t_malloc	**kd_malloc_queue(void);
int			kd_malloc_queue_size(void);
int			kd_maltag_queue_size(char const *tag);
int			kd_malloc_queue_clear(void);
void		kd_enomem(void);

#endif //FT_MALLOC_H
