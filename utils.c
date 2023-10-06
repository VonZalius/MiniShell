/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:55:49 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/05 00:56:17 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_from_until(t_lexer *word, char *cmd, char that, char this)
{
	if (cmd[word->i] == that)
	{
		while (cmd[word->i] == that)
			word->i++;
		while (cmd[word->i] != this)
		{
			if (cmd[word->i] == '\0')
			{
				if (this != ' ')
					printf("There is a -> %c <- missing\n", this);
				return (0);
			}
			if (cmd[word->i] == '\\')
				word->i++;
			word->i++;
		}
	}
	return (1);
}

void	ffl_2(t_lexer *word)
{
	int			i;

	i = 0;
	while (word->arg[i])
		free(word->arg[i++]);
	free(word->arg);
	if (word->word != NULL)
		free(word->word);
}

//Ici on reboot tout les entrée et sortie standart
void	ft_free_lexer(t_lexer *word, char *cmd, int s_stdin, int s_stdout)
{
	t_lexer		*temp;

	if (s_stdin != -42)
	{
		dup2(s_stdin, STDIN_FILENO);
		dup2(s_stdout, STDOUT_FILENO);
		close(s_stdin);
		close(s_stdout);
	}
	while (word != NULL)
	{
		if (word->good != 0 || word->good == 2)
			ffl_2(word);
		temp = word;
		word = word->prev;
		free(temp);
	}
	free (cmd);
	ft_close_handler();
}

t_lexer	*struct_pipe(t_lexer *word, t_lexer *save)
{
	int	s;

	s = word->good;
	close(word->fdwrite);
	save = word;
	word = word->next;
	word->prev = save;
	word->fdpipe = 1;
	word->good = s;
	return (word);
}

void	int_handler(int sig)
{
	if (sig == SIGSEGV)
	{
		exit(1);
	}
	else if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g_signal != 1)
			rl_redisplay();
		(void) sig;
	}
	else
		printf("\n Sorry... What ??\n");
}
