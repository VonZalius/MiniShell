/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:01:06 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/07 13:49:11 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Terminer le shell en quittant le programme
// Pas d'argument, quitter avec succès
// Libérer la mémoire allouée (si nécessaire)

int	exit_with_error(char *error_msg)
{
	printf("%s", error_msg);
	return (1);
}

int	execute_exit(t_lexer *word, char **args)
{
	int	exit_val;
	int	dol;

	dol = word->dol;
	if (args[1] == NULL)
	{
		cleanup(word);
		exit(dol);
	}
	if (args[1] != NULL && args[2] != NULL)
		return (exit_with_error("minishell: exit: too many arguments\n"));
	else if (ft_isnum(args[1]))
	{
		exit_val = ft_atoi(args[1]) % 256;
		cleanup(word);
		exit(exit_val);
	}
	else
	{
		cleanup(word);
		printf("minishell: exit: numeric argument required\n");
		exit(255);
	}
	return (0);
}
