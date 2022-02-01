/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 20:55:34 by swilmer           #+#    #+#             */
/*   Updated: 2022/01/27 03:49:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

char	*kd_strdup(char const *s)
{
	char	*str;

	if (!s)
		s = "";
	str = kd_malloc(sizeof(char) * (kd_strlen(s) + 1));
	if (!str)
		return (str);
	return (kd_strcpy(str, s));
}
