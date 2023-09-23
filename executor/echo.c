/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:01:13 by cmansey           #+#    #+#             */
/*   Updated: 2023/08/07 22:30:28 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

//MODIFIER STRCMP

// Vérifier si l'argument -n est présent
// Ajouter un saut de ligne si nécessaire
void	execute_echo(char **args)
{
	int	i;
	int	add_newline;

	i = 1;
	add_newline = 1;
	if (args[1] != NULL && strcmp(args[1], "-n") == 0)
	{
		add_newline = 0;
		i = 2;
	}
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (add_newline)
		printf("\n");
}
