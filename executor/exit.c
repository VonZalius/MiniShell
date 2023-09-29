/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:01:06 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/29 17:52:08 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

// CODE A REVOIR AVEC LES MALLOC A FREE

// Terminer le shell en quittant le programme
// Pas d'argument, quitter avec succès
// Libérer la mémoire allouée (si nécessaire)
int	execute_exit(char **args, int last_command_status)
{
	if (args[1] == NULL)
		exit(last_command_status);
	if (args[1] != NULL && args[2] != NULL)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	else if (ft_isnum(args[1]))
		exit(atoi(args[1]));
	else
	{
		printf("minishell: exit: numeric argument required\n");
		exit(255);
	}
	return (0);
}
