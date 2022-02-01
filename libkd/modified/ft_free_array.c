/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:52:27 by swilmer           #+#    #+#             */
/*   Updated: 2022/01/27 02:45:41 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

void	*kd_free_array(void **array, int size)
{
	while (size-- > 0)
		array[size] = kd_free(array[size]);
	array = kd_free(array);
	return (NULL);
}
