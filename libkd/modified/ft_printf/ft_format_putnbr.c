/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_putnbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 05:30:15 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/08 17:42:53 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*kd_itoa_leadingzeros(int n, int r, char *str)
{
	int		i;
	int		len;

	if (r == 0 && n == 0)
		return (kd_strdup(""));
	len = kd_max(kd_nbrlen(n), r);
	str = kd_malloc(sizeof(char) * (len + 1));
	if (!str)
		return (str);
	i = 0;
	while (n > 9 || n < -9)
	{
		str[i++] = kd_abs(n % 10) + '0';
		n /= 10;
	}
	str[i++] = kd_abs(n) + '0';
	while (r - i > 0)
		str[i++] = '0';
	if (n < 0)
		str[i++] = '-';
	str[i] = 0;
	return (kd_strrev(str));
}

static char	*kd_format_putnbr_fill(t_format *list, char *s)
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
	while (s[k])
		str[j++] = s[k++];
	s = kd_free(s);
	while (list->leftadjustment && i-- > 0)
		str[j++] = ' ';
	str[j] = 0;
	return (str);
}

char	*kd_format_putnbr(int n, t_format *list, char *s)
{
	if (!list->leftadjustment && list->padding == '0' && list->precision < 0
		&& list->minwidth != 0)
	{
		if (n < 0)
			list->precision = list->minwidth - 1;
		else
			list->precision = list->minwidth;
	}
	s = kd_itoa_leadingzeros(n, list->precision, s);
	if (!s)
		return (s);
	list->maxlen = kd_max(kd_strlen(s), list->precision);
	s = kd_format_putnbr_fill(list, s);
	return (s);
}