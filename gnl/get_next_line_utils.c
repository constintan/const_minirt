/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:49:09 by lajudy            #+#    #+#             */
/*   Updated: 2021/11/09 20:04:57 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}

char	*ft_strljoin(char const *s1, char const *s2, size_t l)
{
	char	*p;
	char	*res;
	int		len;

	if (s2 == NULL)
		return (NULL);
	len = l;
	if (s1)
		len += ft_strlen(s1);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	res = p;
	while (s1 && *s1)
		*p++ = *s1++;
	while (l--)
		*p++ = *s2++;
	*p = '\0';
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	c = (unsigned char)c;
	while (*str != '\0')
	{
		if (*str == c)
			return (str);
		str++;
	}
	if (*str == '\0' && c == '\0')
		return (str);
	else
		return (NULL);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*p;
	int		i;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (*s1)
		p[i++] = *s1++;
	p[i] = '\0';
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	char			*p;
	char			*res;
	unsigned int	slen;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	res = sub;
	if (start < slen)
		p = (char *)&s[start];
	while (len > 0 && *p)
	{
		*sub = *p;
		sub++;
		p++;
		len--;
	}
	*sub = '\0';
	return (res);
}
