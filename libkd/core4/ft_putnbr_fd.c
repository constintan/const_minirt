/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 06:48:56 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/03 06:48:58 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

int	kd_putnbr_fd(int n, int fd)
{
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
	return (kd_putstr_fd(kd_strrev(nbr), fd));
}
