/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 20:52:53 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/08 08:40:22 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

t_list	*kd_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_elem;

	new_lst = NULL;
	while (lst)
	{
		new_elem = kd_lstnew(f(lst->content));
		if (new_elem)
			kd_lstadd_back(&new_lst, new_elem);
		else
			kd_lstclear(&new_lst, del);
		lst = lst->next;
	}
	return (new_lst);
}
