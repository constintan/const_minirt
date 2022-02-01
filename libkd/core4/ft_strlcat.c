/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 20:55:47 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/02 20:55:48 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

size_t	kd_strlcat(char *dst, char const *src, size_t dstsize)
{
	unsigned int	len;

	len = kd_strnlen(dst, dstsize);
	return (len + kd_strlcpy(dst + len, src, dstsize - len));
}
