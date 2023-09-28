/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:15:39 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/28 15:10:12 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Verifier si deja free dans le split libft
void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*char	*combine_path_and_cmd(const char *dir, const char *cmd)
{
	char	*full_path;

	full_path = malloc(strlen(dir) + strlen(cmd) + 2);
	sprintf(full_path, "%s/%s", dir, cmd);
	return (full_path);
}*/

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

/*char	*find_command_path(const char *cmd, char **environ_copy)
{
	char	*path;
	char	**dirs;
	char	*full_path;
	int		i;

	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	i = -1;
	while (environ_copy[++i])
		if (ft_strncmp(environ_copy[i], "PATH=", 5) == 0)
			path = environ_copy[i] + 5;
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	i = -1;
	while (dirs[++i])
	{
		full_path = combine_path_and_cmd(dirs[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			free_array(dirs);
			return (full_path);
		}
		free(full_path);
	}
	free_array(dirs);
	return (NULL);
}*/
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

void	ft_other(t_lexer *word, char **environ)
{
	pid_t		pid;
	char		*full_path;
	//char		**environ_copy;

	pid = fork();
	//environ_copy = duplicate_environ(environ);
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		word->arg[-1] = word->word;
		full_path = find_command_path(word->arg[-1], environ);
		if (full_path)
		{
			execve(full_path, &word->arg[-1], environ);
			free(full_path);
		}
		else
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
}
