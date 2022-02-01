/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 20:57:58 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/02 20:57:59 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

char	*kd_strrchr(char const *s, int c)
{
	unsigned int	i;

	i = kd_strlen(s) + 1;
	while (i-- > 0)
		if (s[i] == (char)c)
			return ((char *)&s[i]);
	return (0);
}
