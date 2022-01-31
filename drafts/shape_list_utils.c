/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: konstanting <konstanting@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:45:51 by konstanting       #+#    #+#             */
/*   Updated: 2022/01/31 22:58:45 by konstanting      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape_list	*new_shape(t_objtype type, void *params)
{
	t_shape_list	*p;

	p = (t_shape_list *)malloc(sizeof(t_shape_list));
	p->type = type;
	p->params = params;
	p->next = NULL;
	return (p);
}

void	add_shape_front(t_shape_list **begin_list, t_objtype type, void *data)
{
	t_shape_list	*ptr;

	ptr = new_shape(type, data);
	ptr->next = *begin_list;
	*begin_list = ptr;
}

