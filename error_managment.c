/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_managment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:12:06 by lajudy            #+#    #+#             */
/*   Updated: 2022/01/27 22:33:55 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int invalid_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 3 || filename[len - 1] != 't'
		|| filename[len - 2] != 'r' || filename[len - 3] != '.')
		return(1);
	return (0);
}

void	ft_error(int err)
{
	if (err == -1)
		ft_putstr_fd("Malloc error!\n", STDERR_FILENO);
	else if (err == 1)
		ft_putstr_fd("Error with filename argument\n", STDERR_FILENO);
	else if (err == 2)
		ft_putstr_fd("Error during file opening\n", STDERR_FILENO);
	exit(err);
}
