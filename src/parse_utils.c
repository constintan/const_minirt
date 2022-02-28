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

void init_resolution(t_scene *scene, char *str)
{
	int err;

	err = 0;
	(void)scene;
	WINDOW_WIDTH = ft_atoi(&str, &err);
	WINDOW_HEIGHT = ft_atoi(&str, &err);
	if (err)
		ft_error(11);
}

int	check_identyfier(char const *s1, char const *s2)
{
	while (*s2 && kd_tolower(*s1) == kd_tolower(*s2))
	{
		s1++;
		s2++;
	}
	if (*s2 == '\0' && (*s1 == '\0' || ft_isspace(*s1)))
		return (1);
	else
		return (0);
}
