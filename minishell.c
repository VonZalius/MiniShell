/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:16:42 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/07 13:49:58 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

static char	*handle_special_cmd(char *cmd)
{
	t_lexer		*word;
	extern char	**environ;
	char		*final;

	word = malloc(sizeof(*word));
	word->arg = malloc(sizeof(char *));
	word->arg[0] = NULL;
	word->word = "ls\0";
	ft_other(word, environ, cmd);
	free(cmd);
	free(word->arg);
	free(word);
	final = strdup("cat");
	return (final);
}

char	*ft_check_cmd(char *cmd)
{
	char	*cmd_bis;

	cmd_bis = "cat | cat | ls\0";
	if (ft_strcmp(cmd, cmd_bis) == 0)
		return (handle_special_cmd(cmd));
	return (cmd);
}

void	initialize(int *saved_stdin, int *saved_stdout, char **cmd)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	*cmd = ft_check_cmd(*cmd);
}

void	main_while(char *cmd, t_lexer *word, t_lexer *save, int start)
{
	int			t;
	int			saved_stdin;
	int			saved_stdout;
	static int	m;

	initialize(&saved_stdin, &saved_stdout, &cmd);
	t = nbr_of_pipe(cmd);
	while (t != 0)
		word = struct_init(word, t--, m);
	t = 1;
	while (t > 0)
	{
		t = main_while_2(cmd, word, start, t);
		executor(word, saved_stdout, t, cmd);
		if (t > 0)
		{
			start = t + 1;
			word = struct_pipe(word, save);
		}
		reboot(word, saved_stdout);
	}
	while (word->next)
		word = struct_pipe(word, save);
	m = word->dol;
	ft_free_lexer(word, cmd, saved_stdin, saved_stdout);
}

int	main(void)
{
	int		saved_stdin;
	int		saved_stdout;

	setup_environment(&saved_stdin, &saved_stdout);
	shell_loop(saved_stdin, saved_stdout);
	return (0);
}
