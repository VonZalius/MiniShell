/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:01:16 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/29 16:39:07 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

//MODIFIER STRCMP STRCPY

// Fonction pour changer le répertoire courant
// Elle prend en paramètres le chemin du répertoire cible et la variable oldpwd
// Obtenir le chemin absolu du répertoire courant
// Mettre à jour la variable oldpwd avec l'ancien chemin
int	change_directory(char *path, char *oldpwd)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	ft_strcpy(oldpwd, cwd);
	return (0);
}

// Prend en paramètres les arguments de la commande et la variable oldpwd
// Argument "..", utiliser la fonction change_directory pour remonter d'un niv
int	execute_cd(char **args, char *oldpwd)
{
	if (args[1] == NULL)
	{
		printf("cd: missing argument\n");
		return (1);
	}
	else if (args[2] != NULL)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	if (ft_strcmp(args[1], "..") == 0)
		return (change_directory("..", oldpwd));
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (oldpwd[0] == '\0')
		{
			printf("cd: error: OLDPWD not set\n");
			return (1);
		}
		printf("%s\n", oldpwd);
		return (change_directory(oldpwd, oldpwd));
	}
	else
		return (change_directory(args[1], oldpwd));
}
