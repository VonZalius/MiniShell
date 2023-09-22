/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:01:16 by cmansey           #+#    #+#             */
/*   Updated: 2023/08/07 22:30:12 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

//MODIFIER STRCMP STRCPY

// Fonction pour changer le répertoire courant
// Elle prend en paramètres le chemin du répertoire cible et la variable oldpwd
// Obtenir le chemin absolu du répertoire courant
// Mettre à jour la variable oldpwd avec l'ancien chemin
void	change_directory(char *path, char *oldpwd)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return ;
	}
	if (chdir(path) == -1)
	{
		perror("cd");
		return ;
	}
	strcpy(oldpwd, cwd);
}

// Prend en paramètres les arguments de la commande et la variable oldpwd
// Argument "..", utiliser la fonction change_directory pour remonter d'un niv
void	execute_cd(char **args, char *oldpwd)
{
	if (args[1] == NULL)
	{
		printf("cd: missing argument\n");
		return ;
	}
	else if (args[2] != NULL)
	{
		printf("cd: too many arguments\n");
		return ;
	}
	if (strcmp(args[1], "..") == 0)
		change_directory("..", oldpwd);
	else if (strcmp(args[1], "-") == 0)
	{
		if (oldpwd[0] == '\0')
		{
			printf("cd: error: OLDPWD not set\n");
			return ;
		}
		printf("%s\n", oldpwd);
		change_directory(oldpwd, oldpwd);
	}
	else
		change_directory(args[1], oldpwd);
}
