/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmpi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 20:55:18 by swilmer           #+#    #+#             */
/*   Updated: 2022/01/27 04:02:47 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

int	kd_strcmpi(char const *s1, char const *s2)
{
	while (*s1 && kd_tolower(*s1) == kd_tolower(*s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)kd_tolower(*s1) - (unsigned char)kd_tolower(*s2));
}
