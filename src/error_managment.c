/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_managment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:12:06 by lajudy            #+#    #+#             */
/*   Updated: 2022/01/29 19:46:44 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	invalid_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 3 || filename[len - 1] != 't'
		|| filename[len - 2] != 'r' || filename[len - 3] != '.')
		return (1);
	return (0);
}

void	ft_error(int err)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (err == -1)
		ft_putstr_fd("Malloc error!\n", STDERR_FILENO);
	else if (err == 1)
		ft_putstr_fd("Error with filename argument\n", STDERR_FILENO);
	else if (err == 2)
		ft_putstr_fd("Error during file opening\n", STDERR_FILENO);
	else if (err == 3)
		ft_putstr_fd("Error during sphere initialization\n", STDERR_FILENO);
	else if (err == 4)
		ft_putstr_fd("Error during camera initialization\n", STDERR_FILENO);
	else if (err == 5)
		ft_putstr_fd("Wrong type identifier\n", STDERR_FILENO);
	else if (err == 6)
		ft_putstr_fd("Error during ambient light init\n", STDERR_FILENO);
	else if (err == 7)
		ft_putstr_fd("Error during lighter initialization\n", STDERR_FILENO);
	else if (err == 8)
		ft_putstr_fd("Error during plane initialization\n", STDERR_FILENO);
	else if (err == 9)
		ft_putstr_fd("Error during cylinder initialization\n", STDERR_FILENO);
	else if (err == 10)
		ft_putstr_fd("Light color specified in the mandatory part\n",
			STDERR_FILENO);
	ft_exit(err);
}
