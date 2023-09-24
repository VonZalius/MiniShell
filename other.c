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

// +2 pour '/' et '\0'
char	*combine_path_and_cmd(const char *dir, const char *cmd)
{
	char	*full_path;

	full_path = malloc(strlen(dir) + strlen(cmd) + 2);
	sprintf(full_path, "%s/%s", dir, cmd);
	return (full_path);
}

char	*find_command_path(const char* cmd, char** environ_copy)
{
	char	*path;
	char	**dirs;
	char	*full_path;
	int		i;

	path = NULL;
	i = -1;
	while (environ_copy[++i])
		if (strncmp(environ_copy[i], "PATH=", 5) == 0)
			path = environ_copy[i] + 5;
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	i = -1;
	full_path = NULL;
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
}

void ft_other(lexer *word, char **environ)
{
	pid_t pid;
	char* 		full_path;
	char		**environ_copy;

    pid = fork();
	environ_copy = duplicate_environ(environ);
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		word->arg[-1] = word->word;
		full_path = find_command_path(word->arg[-1], environ_copy);
		if (full_path)
		{
			execve(full_path, &word->arg[-1], environ_copy);
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