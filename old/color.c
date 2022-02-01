/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 23:22:20 by lajudy            #+#    #+#             */
/*   Updated: 2022/01/29 01:40:02 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	*new_color(unsigned char r, unsigned char g, unsigned char b)
{
	t_color	*result;

	result = (t_color *)malloc(sizeof(t_color));
	if (result == NULL)
		ft_error(-1);
	result->r = r;
	result->g = g;
	result->b = b;
	return (result);
}

// color = new_color_atof(ft_atoc(&str, &err), ft_atoc(&str, &err), ft_atoc(&str, &err));
t_color	*new_color_atoc(char **str, int *err)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = ft_atoc(str, err);
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '\0')
	{
		printf("Color not specified. Init with white color\n");
		return (new_color(255, 255, 255));
	}
	if (**str == ',')
		(*str)++;
	g = ft_atoc(str, err);
	while (ft_isspace(**str))
		(*str)++;
	if (**str == ',')
		(*str)++;
	b = ft_atoc(str, err);

	return (new_color(r, g, b));
}
