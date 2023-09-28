/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:01:13 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/28 12:40:05 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

//MODIFIER STRCMP

// Vérifier si l'argument -n est présent
// Ajouter un saut de ligne si nécessaire

void	write_fd(char *str, int fd)
{
	int	j;

	j = 0;
	while (str[j])
	{
		write(fd, &str[j], 1);
		j++;
	}
}

void	execute_echo(char **args, int fd)
{
	int	i;
	int	add_newline;

	i = 1;
	add_newline = 1;
	if (args[1] != NULL && ft_strcmp(args[1], "-n") == 0)
	{
		add_newline = 0;
		i = 2;
	}
	while (args[i])
	{
		write_fd(args[i], fd);
		//printf("%s", args[i]);
		if (args[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (add_newline)
		write(fd, "\n", 1);
}
