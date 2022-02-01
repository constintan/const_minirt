/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 20:50:24 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/08 03:25:22 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

void	*kd_calloc(size_t count, size_t size)
{
	void	*p;

	p = kd_malloc(count * size);
	if (!p)
		return (p);
	kd_bzero(p, count * size);
	return (p);
}
