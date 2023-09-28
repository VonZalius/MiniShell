/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:07:25 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/28 13:21:42 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	h_m_a_bis(char *cmd, int i_bis)
{
	if (cmd[i_bis] == ' ')
	{
		//printf("X - - - - - >  Space detected [%c]\n", cmd[i_bis]);
		while (cmd[i_bis] == ' ')
			i_bis++;
	}
	else if (cmd[i_bis] == '<' || cmd[i_bis] == '>')
	{
		//printf("X - - - - - >  '<' or '>' detected [%c]\n", cmd[i_bis]);
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
			//printf("X - - - - - >  Word or Argumet detected [%c]\n", cmd[i_bis]);
			while (cmd[i_bis] != ' ' && cmd[i_bis] != '\0'
				&& cmd[i_bis] != '|' && cmd[i_bis] != '<' && cmd[i_bis] != '>')
			{
				i_bis = h_m_a_bis2(cmd, i_bis);
				i_bis++;
			}
			j++;
		}
	}
	//printf("X - - - - - > Total nbr of arg detected = [%i]\n", j - 1);
	/*while (cmd[i_bis] != '\0' && cmd[i_bis] != '|')
	{
		if (i_bis == copy && cmd[i_bis] == ' ')
		{
			while (cmd[i_bis] == ' ')
				i_bis++;
		}
		else if (cmd[i_bis] == '\"')
		{
			i_bis++;
			while (cmd[i_bis] != '\"' && cmd[i_bis] != '\0')
				i_bis++;
			i_bis++;
		}
		else if (cmd[i_bis] == '\'')
		{
			i_bis++;
			while (cmd[i_bis] != '\'' && cmd[i_bis] != '\0')
				i_bis++;
			i_bis++;
		}
		else if (cmd[i_bis] == '<' || cmd[i_bis] == '>')
		{
			while (cmd[i_bis] == '<' || cmd[i_bis] == '>')
				i_bis++;
			j--;
		}
		else if (cmd[i_bis] == ' ')
		{
			while (cmd[i_bis] == ' ')
				i_bis++;
			if (cmd[i_bis] == '|' || cmd[i_bis] == '\0')
				return (j);
			if (cmd[i_bis] == '<' || cmd[i_bis] == '>')
			{
				while (cmd[i_bis] == '<' || cmd[i_bis] == '>')
					i_bis++;
				j--;
			}
			j++;
		}
		else
			i_bis++;

	}*/
	return (j - 1);
}
