/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:01:43 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/02 15:42:43 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Recherche de la variable dans l'environnement
// Suppression de la variable de l'environnement
// On va tout decaler d'une position vers l'arriere

static void	remove_variable(char **existing_var)
{
	char	**next_var;

	next_var = existing_var + 1;
	while (*next_var != NULL)
	{
		*existing_var = *next_var;
		existing_var++;
		next_var++;
	}
	*existing_var = NULL;
}

int	execute_unset(char **args, char ***environ)
{
	char	**existing_var;

	if (args[1] == NULL)
	{
		printf("unset: missing argument\n");
		return (1);
	}
	existing_var = *environ;
	while (*existing_var != NULL)
	{
		if (ft_strncmp(*existing_var, args[1], ft_strlen(args[1])) == 0)
		{
			remove_variable(existing_var);
			return (0);
		}
		existing_var++;
	}
	return (1);
}
