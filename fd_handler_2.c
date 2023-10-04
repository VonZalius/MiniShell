/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 00:26:16 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/05 00:56:24 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_fw_bis(char *cmd, t_lexer *word, int i)
{
	while (cmd[word->i] != ' ' && cmd[word->i] != '<'
		&& cmd[word->i] != '>' && cmd[word->i] != '|' && cmd[word->i] != '\0')
	{
		if (cmd[word->i] != '\"' && cmd[word->i] != '\'')
			i++;
		word->i++;
	}
	return (i);
}

char	*open_fw_bis2(char *cmd, t_lexer *word, int i, char *file)
{
	while (cmd[word->i] != ' ' && cmd[word->i] != '<'
		&& cmd[word->i] != '>' && cmd[word->i] != '|'
		&& cmd[word->i] != '\0')
	{
		if (cmd[word->i] != '\"' && cmd[word->i] != '\'')
		{
			file[i] = cmd[word->i];
			i++;
		}
		word->i++;
	}
	file[i] = '\0';
	return (file);
}
