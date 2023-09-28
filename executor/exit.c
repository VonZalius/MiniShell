/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:01:06 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/28 15:02:29 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

// CODE A REVOIR AVEC LES MALLOC A FREE

// Terminer le shell en quittant le programme
// Pas d'argument, quitter avec succès
// Libérer la mémoire allouée (si nécessaire)
void	execute_exit(char **args)
{
	int	exit_value;

	if (args[1] == NULL)
	{
		exit(EXIT_SUCCESS);
	}
	if (args[1] != NULL && args[2] != NULL)
		printf("minishell: exit: too many arguments\n");
	else
	{
		if (ft_isnum(args[1]))
		{
			exit_value = atoi(args[1]);
			exit(exit_value);
		}
		else
		{
			printf("minishell: exit: numeric argument required\n");
			exit(EXIT_FAILURE);
		}
	}
}
