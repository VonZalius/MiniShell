/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:08:18 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/02 15:42:35 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Allouer de la mémoire pour la nouvelle chaîne
// Copier la partie avant le signe égal
// Concaténer la nouvelle valeur
// Libérer l'ancienne valeur et attribuer la nouvelle valeur
int	update_existing_variable(char **existing_var, char *new_value)
{
	size_t	var_name_length;
	size_t	new_value_length;
	size_t	new_var_length;
	char	*new_var;

	var_name_length = ft_strchr(*existing_var, '=') - *existing_var;
	new_value_length = ft_strlen(new_value);
	new_var_length = var_name_length + new_value_length + 2;
	new_var = (char *)malloc(new_var_length);
	if (!new_var)
		malloc_error_1(new_var);
	ft_strncpy(new_var, *existing_var, var_name_length);
	new_var[var_name_length] = '\0';
	ft_strcat(new_var, "=");
	ft_strcat(new_var, new_value);
	free(*existing_var);
	*existing_var = new_var;
	return (0);
}

// Calculer la taille actuelle de l'environnement
// Allouer de la mémoire pour le nouvel environnement
// Copier les variables de l'ancien environnement vers le nouvel environnement
// Copier la nouvelle variable dans le nouvel environnement
int	add_new_variable(char ***environ, char *var)
{
	int		env_size;
	char	**new_environ;
	int		i;

	env_size = 0;
	while ((*environ)[env_size] != NULL)
		env_size++;
	new_environ = (char **)malloc(sizeof(char *) * (env_size + 2));
	if (!new_environ)
		malloc_error(new_environ);
	i = 0;
	while (i < env_size)
	{
		new_environ[i] = (*environ)[i];
		i++;
	}
	new_environ[env_size] = ft_strdup(var);
	new_environ[env_size + 1] = NULL;
	free(*environ);
	*environ = new_environ;
	return (0);
}

// Remplace une variable dans l'environnement avec une nouvelle valeur
// ou ajoute une nouvelle variable si elle n'existe pas
// Trouver le signe égal dans la variable
// Parcourir les variables existantes dans l'environnement
static char	**find_variable(char *var, char **env, size_t var_name_length)
{
	while (*env)
	{
		if (ft_strncmp(*env, var, var_name_length) == 0)
			return (env);
		env++;
	}
	return (NULL);
}

int	replace_variable(char *var, char ***environ)
{
	char	*equal_sign;
	char	*var_value;
	char	**existing_var;

	equal_sign = ft_strchr(var, '=');
	if (!equal_sign || equal_sign == var)
	{
		printf("export: invalid syntax: %s\n", var);
		return (1);
	}
	var_value = equal_sign + 1;
	existing_var = find_variable(var, *environ, equal_sign - var);
	if (existing_var)
		update_existing_variable(existing_var, var_value);
	else if (!find_variable(var, *environ, ft_strlen(var)))
		add_new_variable(environ, var);
	return (0);
}

//Exécute la commande export en affichant les variables d'environnement
//ou en les mettant à jour
int	execute_export(char **args, char ***environ, int fd)
{
	char	**env;
	int		retval;

	retval = 0;
	if (args[1] == NULL)
	{
		env = *environ;
		while (*env != NULL)
		{
			write_fd(*env, fd);
			write(fd, "\n", 1);
			env++;
		}
	}
	else
		retval = replace_variable(args[1], environ);
	return (retval);
}
