/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:24:13 by lajudy            #+#    #+#             */
/*   Updated: 2021/11/09 19:54:32 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	buf_add(char **buf, int fd)
{
	char	*res;
	int		size;
	char	*tmp;

	res = ft_strdup(*buf);
	free(*buf);
	*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (*buf == NULL)
		return (0);
	*buf[0] = '\0';
	size = read(fd, *buf, BUFFER_SIZE);
	if (size > 0)
	{
		(*buf)[size] = '\0';
		tmp = ft_strljoin(res, *buf, size);
		free(res);
		if (tmp == NULL)
			return (0);
		res = tmp;
	}
	free(*buf);
	*buf = res;
	return (size);
}

char	*get_next_line(int fd)
{
	static char	*buf = NULL;
	char		*result;
	int			size;
	char		*fn;
	char		*cutted;

	if (buf)
		fn = ft_strchr(buf, '\n');
	if (buf && fn)
	{
		result = ft_substr(buf, 0, fn - buf + 1);
		if (*(fn + 1) != '\0')
			cutted = ft_strdup(fn + 1);
		else
			cutted = NULL;
		free(buf);
		buf = cutted;
		return (result);
	}
	size = buf_add(&buf, fd);
	if (size > 0)
		return (get_next_line(fd));
	cutted = buf;
	buf = NULL;
	return (cutted);
}
