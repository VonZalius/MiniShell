/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:16:54 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/28 12:23:25 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_jump_over(char *cmd, t_lexer *word)
{
	if (cmd[word->i] == '|')
		//printf("- - - - - >  Pipe detected [%c]\n", cmd[word->i]);
		return (word->i);
	else if (cmd[word->i] == ' ')
		//printf("- - - - - >  Space detected [%c]\n", cmd[word->i]);
		while (cmd[word->i] == ' ')
			word->i++;
	else if (cmd[word->i] == '<' || cmd[word->i] == '>')
	{
		//printf("- - - - - >  '<' or '>' detected [%c]\n", cmd[word->i]);
		word->i++;
		while (cmd[word->i] == '<' || cmd[word->i] == '>')
			word->i++;
		while (cmd[word->i] == ' ')
			word->i++;
		while (cmd[word->i] != ' ' && cmd[word->i] != '\0' && cmd[word->i]
			!= '|' && cmd[word->i] != '<' && cmd[word->i] != '>')
			word->i++;
	}
	else
		return (-1);
	return (-2);
}

int	cmd_while_for_len(char *cmd, int i_bis, t_lexer *word)
{
	while (cmd[i_bis] != ' ' && cmd[i_bis] != '\0' && cmd[i_bis] != '|'
		&& cmd[i_bis] != '<' && cmd[i_bis] != '>')
	{
		if (cmd[i_bis] == '\'')
		{
			word->quot_check = 1;
			i_bis++;
			while (cmd[i_bis] != '\'')
				i_bis++;
		}
		if (cmd[i_bis] == '\"')
		{
			word->quot_check = 1;
			i_bis++;
			while (cmd[i_bis] != '\"')
				i_bis++;
		}
		i_bis++;
	}
	return (i_bis);
}

int	cmd_malloc(t_lexer *word, int i_bis, int index_arg)
{
	if (word->cmd_check == 0)
	{
		word->word = malloc(sizeof(char) * (i_bis - word->i + 1));
		if (word->word == NULL)
			return (0);
	}
	else
	{
		word->arg[index_arg] = malloc(sizeof(char) * (i_bis - word->i + 1));
		if (word->arg[index_arg] == NULL)
			return (0);
	}
	if (word->i == '\'' || word->i == '\"')
		word->i++;
	return (1);
}

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
			//printf("- - - - - >  Word or Argumet detected [%c]\n", cmd[word->i]);
			i_bis = cmd_while_for_len(cmd, word->i, word);
			if (cmd_malloc(word, i_bis, index_arg) == 0)
				return (0);
			k = 0;
			i_bis = i_bis - word->i;
			if (word->quot_check == 1)
			{
				word->i++;
				i_bis -= 2;
			}
			while (i_bis-- > 0)
			{
				if (word->cmd_check == 0)
					word->word[k++] = cmd[word->i++];
				else
					word->arg[index_arg][k++] = cmd[word->i++];
			}
			index_arg = cmd_terminator(word, index_arg, k);
			if (word->quot_check == 1)
				word->i++;
		}
	}
	return (-1);
}

int	cmd_in_struct(t_lexer *word, char *cmd, int start)
{
	int			i_bis;
	int			j;
	int			index_arg;

	word->i = start;
	index_arg = 0;
	i_bis = 0;
	j = 0;
	j = how_many_arg(cmd, start, j);
	word->arg = (char **)malloc(sizeof(char *) * (j + 1));
	if (word->arg == NULL)
		return (0);
	word->arg[j] = NULL;
	word->cmd_check = 0;
	return (cmd_big_while(cmd, word, index_arg, i_bis));
}
