/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:02:38 by swilmer           #+#    #+#             */
/*   Updated: 2021/12/16 12:47:05 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*kd_free(void *p)
{
	if (p)
		kd_free_queue(p, NULL);
	return (NULL);
}

void	*kd_free_tag(char const *tag)
{
	kd_free_queue(NULL, tag);
	return (NULL);
}

static void	kd_normal_free(void *p)
{
	write(2, "warning: somewhere ft_free processed malloc pointer that "
		"was not processed by ft_malloc first\n", 94);
	free(p);
}

int	kd_free_queue(void *p, char const *tag)
{
	t_malloc	**list;
	t_malloc	*lst;
	int			i;

	list = kd_malloc_queue();
	if (p)
	{
		lst = kd_malloc_lstfind(*list, p);
		if (lst)
		{
			kd_malloc_lstremove(list, lst);
			return (1);
		}
		kd_normal_free(p);
		return (-1);
	}
	lst = kd_maltag_lstfind(*list, tag);
	i = 0;
	while (lst)
	{
		kd_malloc_lstremove(list, lst);
		lst = kd_maltag_lstfind(*list, tag);
		i++;
	}
	return (i);
}

int	kd_free_all(void)
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
		free(lst->content);
		free(lst);
		i++;
	}
	return (i);
}
