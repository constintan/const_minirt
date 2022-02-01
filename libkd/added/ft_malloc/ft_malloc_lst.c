/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:58:59 by swilmer           #+#    #+#             */
/*   Updated: 2021/12/12 23:11:58 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	kd_malloc_lstremove(t_malloc **list, t_malloc *remove)
{
	t_malloc	*temp;

	if (*list == remove)
		*list = (*list)->next;
	else
	{
		temp = *list;
		while (temp->next != remove)
			temp = temp->next;
		temp->next = remove->next;
	}
	free(remove->tag);
	free(remove->content);
	free(remove);
}

t_malloc	*kd_malloc_lstfind(t_malloc *lst, void *find)
{
	while (lst)
	{
		if (lst->content == find)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_malloc	*kd_maltag_lstfind(t_malloc *lst, char const *tag)
{
	int			i;

	while (lst)
	{
		i = 0;
		while (lst->tag && tag && lst->tag[i] && lst->tag[i] == tag[i])
			i++;
		if ((!lst->tag && !tag) || (lst->tag && tag && lst->tag[i] == tag[i]))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

static char	*kd_malloc_lstnew_strdup(char const *tag)
{
	char	*str;
	size_t	len;

	if (!tag)
		return (NULL);
	len = 0;
	while (tag[len])
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	len = 0;
	while (tag[len])
	{
		str[len] = tag[len];
		len++;
	}
	str[len] = tag[len];
	return (str);
}

t_malloc	*kd_malloc_lstnew(void *content, char const *tag)
{
	t_malloc	*lst;

	lst = malloc(sizeof(t_malloc));
	if (!lst)
		return (NULL);
	lst->tag = kd_malloc_lstnew_strdup(tag);
	if (tag && !lst->tag)
	{
		free(lst);
		return (NULL);
	}
	lst->content = content;
	lst->next = NULL;
	return (lst);
}
