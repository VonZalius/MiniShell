/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:16:54 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/05 00:52:26 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_terminator(t_lexer *word, int index_arg, int k)
{
	if (word->cmd_check == 0)
	{
		word->word[k] = '\0';
		word->cmd_check = 1;
	}
	else
	{
		word->arg[index_arg][k] = '\0';
		index_arg++;
	}
	return (index_arg);
}

int	cbw_2(t_lexer *word, char *cmd, int k, int index_arg)
{
	if (word->cmd_check == 0)
		word->word[k++] = cmd[word->i++];
	else
		word->arg[index_arg][k++] = cmd[word->i++];
	return (k);
}

int	cbw_3(t_lexer *word, int i_bis)
{
	word->i++;
	i_bis -= 2;
	return (i_bis);
}

int	cmd_big_while(char *cmd, t_lexer *word, int index_arg, int i_bis)
{
	int	k;

	while (cmd[word->i] != '\0')
	{
		word->quot_check = 0;
		k = cmd_jump_over(cmd, word);
		if (k > -1)
			return (k);
		if (k == -1)
		{
			i_bis = cmd_while_for_len(cmd, word->i, word);
			if (cmd_malloc(word, i_bis, index_arg) == 0)
				return (0);
			k = 0;
			i_bis = i_bis - word->i;
			if (word->quot_check == 1)
				i_bis = cbw_3(word, i_bis);
			while (i_bis-- > 0)
				k = cbw_2(word, cmd, k, index_arg);
			index_arg = cmd_terminator(word, index_arg, k);
			if (word->quot_check == 1)
				word->i++;
		}
	}
	return (-1);
}

int	cmd_in_struct(t_lexer *word, char *cmd, int start)
{
	int			j;
	int			index_arg;
	int			i_bis;

	i_bis = 0;
	word->i = start;
	index_arg = 0;
	j = 0;
	j = how_many_arg(cmd, start, j);
	word->arg = (char **)malloc(sizeof(char *) * (j + 1));
	if (word->arg == NULL)
		return (0);
	word->arg[j] = NULL;
	word->cmd_check = 0;
	return (cmd_big_while(cmd, word, index_arg, i_bis));
}
