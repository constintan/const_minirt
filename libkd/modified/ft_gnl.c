/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 09:24:22 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/08 09:24:31 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

static char	*kd_gnl_recursion(int fd, int *i, int *r)
{
	static char	b[BUFFER_SIZE];
	char		*s;
	int			x;

	s = NULL;
	x = *i;
	while (*i < *r)
		if (b[(*i)++] == '\n')
			break ;
	if (*i > x)
	{
		s = kd_substring(b, x, *i);
		if (!s || b[*i - 1] == '\n' || *r < BUFFER_SIZE)
			return (s);
	}
	*i = 0;
	*r = read(fd, b, BUFFER_SIZE);
	if (s && *r <= 0)
		return (s);
	if (s)
		return (kd_strjoin_free(s, kd_gnl_recursion(fd, i, r), 0));
	if (*r > 0)
		return (kd_gnl_recursion(fd, i, r));
	return (s);
}

char	*kd_gnl(int fd)
{
	static int	i;
	static int	r;

	return (kd_gnl_recursion(fd, &i, &r));
}
