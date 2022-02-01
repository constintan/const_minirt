/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 16:58:58 by swilmer           #+#    #+#             */
/*   Updated: 2022/01/27 03:42:25 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

char	*kd_strjoin_free(char *s1, char *s2, int option)
{
	char	*str;

	str = kd_strjoin(s1, s2);
	if (option == 0 || option == 1)
		kd_free(s1);
	if (option == 0 || option == 2)
		kd_free(s2);
	return (str);
}
