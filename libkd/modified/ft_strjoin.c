/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 20:55:39 by swilmer           #+#    #+#             */
/*   Updated: 2022/01/27 14:01:42 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

char	*kd_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (!s1 && s2)
		return (kd_strdup(s2));
	else if (s1 && !s2)
		return (kd_strdup(s1));
	else if (!s1 && !s2)
		return (kd_strdup(""));
	str = kd_malloc(sizeof(char) * (kd_strlen(s1) + kd_strlen(s2) + 1));
	if (!str)
		return (str);
	kd_stpcpy(kd_stpcpy(str, s1), s2);
	return (str);
}
