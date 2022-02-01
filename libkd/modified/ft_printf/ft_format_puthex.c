/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_puthex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 05:29:52 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/08 18:27:48 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*kd_format_puthex_hex(unsigned int n, int r, char *str)
{
	int			uilen;
	int			j;
	int			len;

	if (r == 0 && n == 0)
		return (kd_strdup(""));
	j = 0;
	uilen = sizeof(n) * 2;
	while (j < uilen - 1 && !((n >> ((uilen - 1 - j) * 4)) & 0xf))
		j++;
	len = uilen - j;
	str = kd_malloc(sizeof(char) * (kd_max(len, r) + 1));
	if (!str)
		return (str);
	j = 0;
	while (r-- > len)
		str[j++] = '0';
	while (len > 0)
		str[j++] = "0123456789abcdef"[(n >> ((len-- - 1) * 4)) & 0xf];
	str[j] = 0;
	return (str);
}

static char	*kd_format_puthex_fill(t_format *list, char *s)
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
		str[j++] = ' ';
	while (s[k] && list->conversion == 'X')
		str[j++] = kd_toupper(s[k++]);
	while (s[k] && list->conversion == 'x')
		str[j++] = s[k++];
	s = kd_free(s);
	while (list->leftadjustment && i-- > 0)
		str[j++] = ' ';
	str[j] = 0;
	return (str);
}

char	*kd_format_puthex(unsigned int n, t_format *list, char *s)
{
	if (!list->leftadjustment && list->padding == '0' && list->precision < 0
		&& list->minwidth != 0)
		list->precision = list->minwidth;
	s = kd_format_puthex_hex(n, list->precision, s);
	if (!s)
		return (s);
	list->maxlen = kd_max(kd_strlen(s), list->precision);
	s = kd_format_puthex_fill(list, s);
	return (s);
}
