/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 21:00:50 by swilmer           #+#    #+#             */
/*   Updated: 2022/01/27 13:59:16 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

char	*kd_substr(char const *src, unsigned int start, size_t len)
{
	char	*str;

	if (!src)
		return (kd_strdup(""));
	if (kd_strnlen(src, start) == start)
		len = kd_strnlen(src + start, len);
	else
		len = 0;
	str = kd_malloc(sizeof(char) * (len + 1));
	if (!str)
		return (str);
	kd_memcpy(str, src + start, len);
	str[len] = 0;
	return (str);
}
