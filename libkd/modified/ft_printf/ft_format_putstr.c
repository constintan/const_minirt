/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_putstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 05:30:04 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/08 17:43:33 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*kd_format_putstr_fill(t_format *list, char *s)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 0;
	while (list->minwidth-- > list->maxlen)
		i++;
	str = kd_malloc(sizeof(char) * (i + kd_strlen(s) + 1));
	if (!str)
		return (str);
	j = 0;
	k = 0;
	while (!list->leftadjustment && i-- > 0)
		str[j++] = list->padding;
	while (s[k] && list->precision-- != 0)
		str[j++] = s[k++];
	s = kd_free(s);
	while (list->leftadjustment && i-- > 0)
		str[j++] = ' ';
	str[j] = 0;
	return (str);
}

char	*kd_format_putstr(char const *str, t_format *list, char *s)
{
	if (str)
		s = kd_strdup(str);
	else
		s = kd_strdup("(null)");
	if (!s)
		return (s);
	if (list->precision < 0)
		list->maxlen = kd_strlen(s);
	else
		list->maxlen = kd_min(kd_strlen(s), list->precision);
	s = kd_format_putstr_fill(list, s);
	return (s);
}
