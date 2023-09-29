/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:55:49 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/28 16:44:27 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}*/

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

void	ft_free_lexer(t_lexer *word, char *cmd, int s_stdin, int s_stdout)
{
	t_lexer		*temp;
	int			i;
	int			j;

	//Ici on reboot tout les entrée et sortie standart
		dup2(s_stdin, STDIN_FILENO);
		dup2(s_stdout, STDOUT_FILENO);
		close(s_stdin);
		close(s_stdout);
	while (word != NULL)
	{
		i = 0;
		while (i < how_many_arg(cmd, 0, 0))
			free(word->arg[i++]);
		free(word->arg);
		if (word->word != NULL)
			free(word->word);
		temp = word;
		word = word->prev;
		free(temp);
	}
	free (cmd);
	j = open("pipe_handler", O_RDWR | O_TRUNC | O_CREAT, 0644);
	close(j);
	j = open("double_handler", O_RDWR | O_TRUNC | O_CREAT, 0644);
	close(j);
	j = open("pipe_handler_2", O_RDWR | O_TRUNC | O_CREAT, 0644);
	close(j);
}

void	int_handler(int sig)
{
	if (sig == SIGSEGV)
	{
		printf("\nYou press -D\n");
		exit(1);
	}
	else if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		(void) sig;
	}
	else
		printf("\n Sorry... What ??\n");
}
