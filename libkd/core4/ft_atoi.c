/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 20:49:59 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/02 20:50:03 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

int	kd_atoi(char const *str)
{
	short	u;
	int		n;

	u = 1;
	n = 0;
	while (kd_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			u = -1;
	while (kd_isdigit(*str))
		n = n * 10 + *str++ - '0';
	return (n * u);
}
