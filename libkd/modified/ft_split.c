/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 20:54:47 by swilmer           #+#    #+#             */
/*   Updated: 2022/01/27 14:09:41 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libkd.h"

static unsigned int	kd_split_words(char ***strings, char const *str, char c)
{
	unsigned int	count_words;
	unsigned int	i;
	unsigned int	word_start;

	count_words = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] != c)
		{
			word_start = i;
			while (str[i] != c && str[i])
				i++;
			if (*strings)
			{
				(*strings)[count_words] = kd_substring(str, word_start, i);
				if (!(*strings)[count_words])
					return (0);
			}
			count_words++;
		}
		else
			i++;
	}
	return (count_words);
}

char	**kd_split(char const *str, char c)
{
	char			**strings;
	unsigned int	count_words;
	unsigned int	check_words;

	strings = NULL;
	count_words = kd_split_words(&strings, str, c);
	strings = kd_malloc(sizeof(char *) * (count_words + 1));
	if (!strings)
		return (strings);
	check_words = kd_split_words(&strings, str, c);
	strings[check_words] = NULL;
	if (check_words != count_words)
		return (kd_free_strings(strings));
	return (strings);
}
