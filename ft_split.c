/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 02:40:56 by lajudy            #+#    #+#             */
/*   Updated: 2022/01/27 22:41:20 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	**ft_array_allocate(char const *s, char c, int *size)
{
	char	**array;

	*size = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
		{
			*size = *size + 1;
			s++;
		}
		while (*s != c && *s)
			s++;
	}
	array = (char **)malloc(sizeof(char *) * (*size + 1));
	if (array == NULL)
		return (NULL);
	return (array);
}

static char	**ft_lines_allocate(char **array, char const *s, char c, int size)
{
	int	i;
	int	sub_len;

	i = -1;
	while (++i < size && *s)
	{
		while (*s == c && *s)
			s++;
		sub_len = 0;
		while (*s != c && *s)
		{
			sub_len++;
			s++;
		}
		array[i] = (char *)malloc(sizeof(char) * (sub_len + 1));
		if (array[i] == NULL)
		{
			while (--i >= 0)
				free(array[i]);
			free(array);
			return (NULL);
		}
	}
	array[i] = NULL;
	return (array);
}

static char	**ft_fill_array(char **array, char const *s, char c, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		while (*s == c && *s)
			s++;
		j = 0;
		while (*s != c && *s)
		{
			array[i][j] = *s;
			j++;
			s++;
		}
		array[i][j] = '\0';
		i++;
	}
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		size;

	if (s == NULL)
		return (NULL);
	array = ft_array_allocate(s, c, &size);
	if (array == NULL)
		return (NULL);
	array = ft_lines_allocate(array, s, c, size);
	if (array == NULL)
		return (NULL);
	array = ft_fill_array(array, s, c, size);
	if (array == NULL)
		return (NULL);
	return (array);
}

int	splited_size(char **words)
{
	int	size;

	size = 0;
	while (words && *words)
	{
		words++;
		size++;
	}
	return (size);
}
