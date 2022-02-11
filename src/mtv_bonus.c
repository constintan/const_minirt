/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtv.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:06:03 by swilmer           #+#    #+#             */
/*   Updated: 2022/02/11 14:41:01 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

long	mtv(void)
{
	struct timeval	tv;
	static long		start;

	gettimeofday(&tv, NULL);
	if (!start)
	{
		start = (long) tv.tv_sec * 1000 + tv.tv_usec / 1000;
		return (0);
	}
	return (((long)tv.tv_sec * 1000 + tv.tv_usec / 1000) - start);
}
