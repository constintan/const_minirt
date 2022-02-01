/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 20:57:00 by swilmer           #+#    #+#             */
/*   Updated: 2022/01/27 14:17:03 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

char	*kd_strmapi(char const *src, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	if (!src)
		return (kd_strdup(""));
	str = kd_malloc(sizeof(char) * (kd_strlen(src) + 1));
	if (!str)
		return (str);
	i = 0;
	while (src[i])
	{
		str[i] = (*f)(i, src[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}
