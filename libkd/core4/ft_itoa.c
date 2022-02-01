/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 20:51:46 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/08 03:26:00 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

char	*kd_itoa(int n)
{
	char			*str;
	char			nbr[12];
	unsigned short	i;

	i = 0;
	while (n > 9 || n < -9)
	{
		nbr[i++] = kd_abs(n % 10) + '0';
		n /= 10;
	}
	nbr[i++] = kd_abs(n) + '0';
	if (n < 0)
		nbr[i++] = '-';
	nbr[i] = 0;
	str = kd_malloc(sizeof(char) * (i + 1));
	if (!str)
		return (str);
	return (kd_strcpy(str, kd_strrev(nbr)));
}
