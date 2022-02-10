/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:08:54 by lajudy            #+#    #+#             */
/*   Updated: 2022/02/01 22:24:30 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3	new_vector_atof(char **str, int *err)
{
	double	x;
	double	y;
	double	z;

	x = ft_atof(str, err);
	while (ft_isspace(**str))
		(*str)++;
	if (**str == ',')
		(*str)++;
	y = ft_atof(str, err);
	while (ft_isspace(**str))
		(*str)++;
	if (**str == ',')
		(*str)++;
	z = ft_atof(str, err);
	return (new_vector3(x, y, z));
}
