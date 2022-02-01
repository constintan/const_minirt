/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 21:02:21 by swilmer           #+#    #+#             */
/*   Updated: 2022/01/27 02:54:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../../added/ft_malloc/ft_malloc.h"
# include "../../libkd.h"
# include <stdarg.h> //va_start, va_arg, va_end

typedef struct s_format
{
	int				minwidth;
	int				leftadjustment;
	char			padding;
	int				precision;
	char			conversion;
	int				maxlen;
}					t_format;

t_format		*kd_format_lstnew(void);
int				kd_format_lstreset(t_format *list);
char			*kd_format_putchar(char c, t_format *list, char *s);
char			*kd_format_puthex(unsigned int n, t_format *list, char *s);
char			*kd_format_putnbr_uint(unsigned int n, t_format *list, char *s);
char			*kd_format_putnbr(int n, t_format *list, char *s);
char			*kd_format_putptr(void *p, t_format *list, char *s);
char			*kd_format_putstr(char const *str, t_format *list, char *s);
char			*kd_conversion_read(char const **format, va_list *va,
					t_format *list, char *s);
int				kd_printf(char const *format, ...);

#endif //FT_PRINTF_H
