/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 21:00:55 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/02 21:00:57 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

char	*kd_substring(char const *src, unsigned int start, unsigned int end)
{
	if (end < start)
		end = start;
	return (kd_substr(src, start, end - start));
}
