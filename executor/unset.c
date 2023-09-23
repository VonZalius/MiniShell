/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:01:43 by cmansey           #+#    #+#             */
/*   Updated: 2023/08/07 22:33:48 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

//STRNCMP STRLEN A MODIFIER

// Recherche de la variable dans l'environnement
// Suppression de la variable de l'environnement
// On va tout decaler d'une position vers l'arriere
void	execute_unset(char **args, char ***environ)
{
	char	**existing_var;
	char	**next_var;

	if (args[1] == NULL)
	{
		printf("unset: missing argument\n");
		return ;
	}
	existing_var = *environ;
	while (*existing_var != NULL)
	{
		if (strncmp(*existing_var, args[1], strlen(args[1])) == 0)
		{
			next_var = existing_var + 1;
			while (*next_var != NULL)
			{
				*existing_var = *next_var;
				existing_var++;
				next_var++;
			}
			*existing_var = NULL;
			return ;
		}
		existing_var++;
	}
}
