/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 22:25:01 by cmansey           #+#    #+#             */
/*   Updated: 2023/08/07 22:28:43 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

//STRDUP

// Fonction pour dupliquer un tableau d'environnement
char	**duplicate_environ(char **environ)
{
	int		i;
	int		env_size;
	char	**new_environ;

	env_size = 0;
	while (environ[env_size])
		env_size++;
	new_environ = (char **)malloc(sizeof(char *) * (env_size + 1));
	if (!new_environ)
		malloc_error(new_environ);
	i = 0;
	while (i < env_size)
	{
		new_environ[i] = strdup(environ[i]);
		if (!new_environ[i])
			malloc_error(new_environ);
		i++;
	}
	new_environ[env_size] = NULL;
	return (new_environ);
}

// Fonction pour libérer la mémoire d'un tableau d'environnement
void	free_environ(char **environ)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		free(environ[i]);
		i++;
	}
	free(environ);
}
