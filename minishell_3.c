/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 01:00:13 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/05 01:24:14 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Ici on reboot tout les entrée et sortie standart
//Ici on séquence l'input !!

int	nbr_of_pipe(char *cmd)
{
	int	t;
	int	i;

	t = 1;
	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"' && cmd [i] != '\0')
				i++;
		}
		else if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'' && cmd [i] != '\0')
				i++;
		}
		else if (cmd[i] == '|')
			t++;
		if (cmd[i] != '\0')
			i++;
	}
	return (t);
}

void	setup_environment(int *saved_stdin, int *saved_stdout)
{
	*saved_stdout = dup(STDOUT_FILENO);
	*saved_stdin = dup(STDIN_FILENO);
	g_signal = 0;
	signal(SIGSEGV, int_handler);
	signal(SIGINT, int_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	shell_loop(int saved_stdin, int saved_stdout)
{
	char	*cmd;
	t_lexer	*word;
	t_lexer	*save;
	int		start;

	while (1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		cmd = readline("Prompt > ");
		if (cmd == NULL)
			exit(0);
		add_history(cmd);
		word = NULL;
		save = NULL;
		start = 0;
		main_while(cmd, word, save, start);
	}
}

void	ft_reboot(t_lexer *word, int saved_stdout)
{
	if (word->fdwrite != 0)
		close(word->fdwrite);
	if (word->fdread != 0)
		close(word->fdread);
	dup2(saved_stdout, STDOUT_FILENO);
}

int	main_while_2(char *cmd, t_lexer *word, int start, int t)
{
	pipe_init(word);
	cmd = env_write_read(cmd, word, start);
	if (word->good == 1)
		t = last_check(cmd, word, start, t);
	else
		t = 0;
	pipe_out(word, t);
	if (word->free_check != 0)
		free(cmd);
	return (t);
}
