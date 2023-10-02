/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:01:28 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/02 15:42:21 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_env(char **environ, int fd)
{
	char	**env;

	env = environ;
	while (*env != NULL)
	{
		if (write_fd(*env, fd) == -1)
			return (1);
		if (write(fd, "\n", 1) == -1)
			return (1);
		env++;
	}
	return (0);
}
