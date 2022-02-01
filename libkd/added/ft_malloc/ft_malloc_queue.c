/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_queue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:01:44 by swilmer           #+#    #+#             */
/*   Updated: 2021/12/16 00:30:33 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_malloc	**kd_malloc_queue(void)
{
	static t_malloc	*list;

	return (&list);
}

int	kd_malloc_queue_size(void)
{
	t_malloc	*lst;
	int			size;

	lst = *kd_malloc_queue();
	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

int	kd_maltag_queue_size(char const *tag)
{
	t_malloc	*lst;
	int			size;
	int			i;

	lst = *kd_malloc_queue();
	size = 0;
	while (lst)
	{
		i = 0;
		while (lst->tag && tag && lst->tag[i] && lst->tag[i] == tag[i])
			i++;
		if ((!lst->tag && !tag) || (lst->tag && tag && lst->tag[i] == tag[i]))
			size++;
		lst = lst->next;
	}
	return (size);
}

int	kd_malloc_queue_clear(void)
{
	t_malloc	**list;
	t_malloc	*lst;
	int			i;

	list = kd_malloc_queue();
	i = 0;
	while (*list)
	{
		lst = *list;
		*list = (*list)->next;
		free(lst->tag);
		free(lst);
		i++;
	}
	return (i);
}

void	kd_enomem(void)
{
}
//write(2, "Cannot allocate memory\n", 23);
//ft_free_all();
//exit(EXIT_FAILURE);