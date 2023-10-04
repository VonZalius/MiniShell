/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:07:25 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/05 00:52:21 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_jump_over(char *cmd, t_lexer *word)
{
	if (cmd[word->i] == '|')
		return (word->i);
	else if (cmd[word->i] == ' ')
		while (cmd[word->i] == ' ')
			word->i++;
	else if (cmd[word->i] == '<' || cmd[word->i] == '>')
	{
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

int	h_m_a_bis(char *cmd, int i_bis)
{
	if (cmd[i_bis] == ' ')
	{
		while (cmd[i_bis] == ' ')
			i_bis++;
	}
	else if (cmd[i_bis] == '<' || cmd[i_bis] == '>')
	{
		while (cmd[i_bis] == '<' || cmd[i_bis] == '>')
			i_bis++;
		while (cmd[i_bis] == ' ')
			i_bis++;
		while (cmd[i_bis] != ' ' && cmd[i_bis] != '\0'
			&& cmd[i_bis] != '|' && cmd[i_bis] != '<' && cmd[i_bis] != '>')
			i_bis++;
	}
	return (i_bis);
}

int	h_m_a_bis2(char *cmd, int i_bis)
{
	if (cmd[i_bis] == '\'')
	{
		i_bis++;
		while (cmd[i_bis] != '\'')
			i_bis++;
	}
	if (cmd[i_bis] == '\"')
	{
		i_bis++;
		while (cmd[i_bis] != '\"')
			i_bis++;
	}
	return (i_bis);
}

int	how_many_arg(char *cmd, int i_bis, int j)
{
	if (cmd == NULL)
		return (0);
	while (cmd[i_bis] != '\0' && cmd[i_bis] != '|')
	{
		if (cmd[i_bis] == ' ' || cmd[i_bis] == '<' || cmd[i_bis] == '>')
			i_bis = h_m_a_bis(cmd, i_bis);
		else
		{
			while (cmd[i_bis] != ' ' && cmd[i_bis] != '\0'
				&& cmd[i_bis] != '|' && cmd[i_bis] != '<' && cmd[i_bis] != '>')
			{
				i_bis = h_m_a_bis2(cmd, i_bis);
				i_bis++;
			}
			j++;
		}
	}
	if (j == 0)
		return (j);
	return (j - 1);
}
