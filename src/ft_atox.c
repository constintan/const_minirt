/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 03:34:19 by lajudy            #+#    #+#             */
/*   Updated: 2022/01/29 00:36:46 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	fraction_part(char **str, int *err)
{
	double	n;
	double	ten_power;

	n = 0;
	if (**str == '.')
	{
		(*str)++;
		ten_power = 1;
		while (**str && ft_isdigit(**str))
		{
			*err = 0;
			ten_power /= 10;
			n = n + ((**str - '0') * ten_power);
			(*str)++;
		}
	}
	return (n);
}

double	ft_atof(char **str, int *err)
{
	double	n;
	int		sign;
	int		local_err;

	while (ft_isspace(**str))
		(*str)++;
	sign = 1;
	local_err = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	n = 0;
	while (**str && ft_isdigit(**str))
	{
		local_err = 0;
		n = 10 * n + (**str - '0');
		(*str)++;
	}
	n += fraction_part(str, &local_err);
	if (*err == 0)
		*err = local_err;
	return (n * sign);
}

unsigned char	ft_atoc(char **str, int *err)
{
	int	n;
	int	local_err;

	while (ft_isspace(**str))
		(*str)++;
	local_err = 1;
	if (**str == '+')
		(*str)++;
	n = 0;
	while (**str && ft_isdigit(**str))
	{
		local_err = 0;
		n = 10 * n + (**str - '0');
		(*str)++;
	}
	if (n > 255)
		local_err = 1;
	if (*err == 0)
		*err = local_err;
	return ((unsigned char) n);
}
