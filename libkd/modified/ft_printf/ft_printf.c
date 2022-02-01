/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 05:30:51 by swilmer           #+#    #+#             */
/*   Updated: 2021/10/09 18:23:19 by swilmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*kd_strchr_mod(char const *s, int c)
{
	char	*chr;

	chr = kd_strchr(s, c);
	if (!chr)
		return (kd_strchr(s, '\0'));
	return (chr);
}

static char	*kd_parse_format(char const *format, va_list *va, t_format *list,
	char *s)
{
	char	*chr;

	if (!*format)
		return (kd_strdup(""));
	while (*format)
	{
		if (*format == '%' && kd_format_lstreset(list))
			s = kd_strjoin_free(s, kd_conversion_read(&format, va, list, s), 0);
		else
		{
			chr = kd_strchr_mod(format, '%');
			s = kd_strjoin_free(s, kd_substr(format, 0, chr - format), 0);
			format = chr - 1;
		}
		if (!s)
			return (s);
		format++;
	}
	return (s);
}

int	kd_printf(char const *format, ...)
{
	t_format	*list;
	char		*s;
	va_list		va;
	int			count;

	list = kd_format_lstnew();
	if (!list)
		return (-1);
	s = NULL;
	va_start(va, format);
	s = kd_parse_format(format, &va, list, s);
	va_end(va);
	if (!s)
		return (-1);
	count = kd_putstr(s);
	list = kd_free(list);
	s = kd_free(s);
	return (count);
}
