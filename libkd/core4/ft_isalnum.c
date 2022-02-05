/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 20:50:44 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/02 20:50:45 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

int	kd_isalnum(int c)
{
	return (kd_isdigit(c) || kd_isalpha(c));
}