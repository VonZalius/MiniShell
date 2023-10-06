/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:15:39 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/05 01:20:32 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_values(t_lexer *word, int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		word->dol = WEXITSTATUS(status);
		if (word->dol != 0)
		{
			word->good = 2;
		}
	}
}

static void	child_process(t_lexer *word, char **environ, char *cmd)
{
	char	*full_path;
	char	**args;

	args = make_args(word);
	full_path = find_command_path(args[0], environ);
	if (full_path)
	{
		if (execve(full_path, &args[0], environ) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		free(args);
		ft_free_lexer(word, cmd, -42, -42);
		exit(1);
	}
}

void	ft_other(t_lexer *word, char **environ, char *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
		child_process(word, environ, cmd);
	else
		ft_values(word, pid);
}
