/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 06:48:40 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/03 06:48:42 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

int	kd_putendl_fd(char *s, int fd)
{
	int	i;

	i = kd_putstr_fd(s, fd);
	if (i < 0)
		return (i);
	if (kd_putchar_fd('\n', fd) < 0)
		return (-1);
	return (i + 1);
}
