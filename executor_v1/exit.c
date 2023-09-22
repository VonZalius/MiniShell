/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:01:06 by cmansey           #+#    #+#             */
/*   Updated: 2023/08/07 17:43:18 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

// CODE A REVOIR AVEC LES MALLOC A FREE

// Terminer le shell en quittant le programme
// Pas d'argument, quitter avec succès
// Libérer la mémoire allouée (si nécessaire)
void	execute_exit(char **args)
{
	if (args[1] == NULL)
	{
		exit(EXIT_SUCCESS);
	}
	/*else
	{
		if (ft_isnum(args[1]))
		{
			int exit_value = atoi(args[1]);

			// ATTENTION A MODIFIER POUR LIBERER MEMOIRE

			// Quitter le programme avec le code de sortie spécifié
			exit(exit_value);
		}
		else
		{
			printf("minishell: exit: numeric argument required\n");
			// ATTENTION A MODIFIER POUR LIBERER MEMOIRE

			// Quitter le programme avec un code d'erreur
			exit(EXIT_FAILURE);
		}
	}*/
}
