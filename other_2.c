/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 01:18:21 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/05 01:24:13 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*combine_path_and_cmd(const char *dir, const char *cmd)
{
	char	*full_path;

	full_path = malloc(strlen(dir) + strlen(cmd) + 2);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, dir);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, cmd);
	return (full_path);
}

char	*get_path_from_env(char **environ_copy)
{
	int	i;

	i = -1;
	while (environ_copy[++i])
		if (ft_strncmp(environ_copy[i], "PATH=", 5) == 0)
			return (environ_copy[i] + 5);
	return (NULL);
}

char	*find_cmd_in_dirs(const char *cmd, char **dirs)
{
	char	*full_path;
	int		i;

	i = -1;
	while (dirs[++i])
	{
		full_path = combine_path_and_cmd(dirs[i], cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

char	*find_command_path(const char *cmd, char **environ_copy)
{
	char	*path;
	char	**dirs;
	char	*full_path;

	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	path = get_path_from_env(environ_copy);
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	full_path = find_cmd_in_dirs(cmd, dirs);
	free_array(dirs);
	return (full_path);
}
