/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strimplode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 07:13:57 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/08 03:35:44 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

char	*kd_strimplode(char **strs, char *sep)
{
	char			*str;
	char			*p;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (strs[j])
		i += kd_strlen(strs[j++]);
	if (j > 0)
		i += kd_strlen(sep) * (j - 1);
	str = kd_malloc(sizeof(char) * (i + 1));
	if (!str)
		return (str);
	p = str;
	i = 0;
	while (i < j)
	{
		str = kd_stpcpy(str, strs[i]);
		if (i < j - 1)
			str = kd_stpcpy(str, sep);
		i++;
	}
	*str = 0;
	return (p);
}
