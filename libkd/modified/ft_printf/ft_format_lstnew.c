/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_lstnew.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 05:29:07 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/08 17:41:47 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_format	*kd_format_lstnew(void)
{
	t_format	*list;

	list = kd_malloc(sizeof(t_format));
	if (!list)
		return (list);
	kd_format_lstreset(list);
	return (list);
}
