/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 20:53:01 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/08 03:26:40 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

t_list	*kd_lstnew(void *content)
{
	t_list	*list;

	list = kd_malloc(sizeof(t_list));
	if (!list)
		return (list);
	list->content = content;
	list->next = NULL;
	return (list);
}
