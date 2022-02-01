/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 05:30:51 by swilmer           #+#    #+#             */
/*   Updated: 2022/01/27 16:57:20 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

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

char	*kd_strf(char const *format, ...)
{
	t_format	*list;
	char		*s;
	va_list		va;

	list = kd_format_lstnew();
	if (!list)
		return (NULL);
	s = NULL;
	va_start(va, format);
	s = kd_parse_format(format, &va, list, s);
	va_end(va);
	if (!s)
		return (s);
	list = kd_free(list);
	return (s);
}
