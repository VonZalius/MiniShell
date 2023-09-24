/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:01:28 by cmansey           #+#    #+#             */
/*   Updated: 2023/08/07 22:30:33 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	execute_env(char **environ, int fd)
{
	char	**env;

	env = environ;
	while (*env != NULL)
	{
		write_fd(*env, fd);
			write(fd, "\n", 1);
		//printf("%s\n", *env);
		env++;
	}
}
