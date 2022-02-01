/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_debug.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:01:44 by swilmer           #+#    #+#             */
/*   Updated: 2021/12/13 15:37:58 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int	kd_malloc_queue_debug_strlen(char const str[])
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	kd_malloc_queue_debug_itoa(char str[], int n)
{
	int			i;
	int			len;

	i = n;
	if (i == 0)
		len = 1;
	else
	{
		len = 0;
		while (i > 0)
		{
			i /= 10;
			len++;
		}
	}
	i = 0;
	while (i < len)
	{
		str[len - i - 1] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	str[i] = '\0';
}

static void	kd_malloc_debug_process_tag(t_malloc **tags, char const *tag)
{
	t_malloc	*newtag;
	char		str[11];

	newtag = kd_malloc_lstnew(NULL, tag);
	if (!newtag)
		kd_enomem();
	newtag->next = *tags;
	*tags = newtag;
	if (tag)
		write(2, tag, kd_malloc_queue_debug_strlen(tag));
	else
		write(2, "(null)", 6);
	write(2, ": ", 2);
	kd_malloc_queue_debug_itoa(str, kd_maltag_queue_size(tag));
	write(2, str, kd_malloc_queue_debug_strlen(str));
	write(2, "\n", 1);
}

void	kd_malloc_debug(void)
{
	t_malloc	*tags;
	t_malloc	*lst;

	tags = NULL;
	lst = *kd_malloc_queue();
	write(2, "\nDEBUG MALLOC\n", 14);
	while (lst)
	{
		if (!kd_maltag_lstfind(tags, lst->tag))
			kd_malloc_debug_process_tag(&tags, lst->tag);
		lst = lst->next;
	}
	write(2, "END OF DEBUG MALLOC\n", 20);
	while (tags)
	{
		lst = tags;
		tags = tags->next;
		free(lst->tag);
		free(lst);
	}
}

void	kd_maltag_debug(char const *tag)
{
	int			len;
	char		str[11];

	write(2, "\nDEBUG MALLOC TAG ", 18);
	if (tag)
	{
		len = 0;
		while (tag[len])
			len++;
		write(2, tag, len);
	}
	else
		write(2, "(null)", 6);
	write(2, ": ", 2);
	kd_malloc_queue_debug_itoa(str, kd_maltag_queue_size(tag));
	len = 0;
	while (str[len])
		len++;
	write(2, str, len);
	write(2, "\n", 1);
}
