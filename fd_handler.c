/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:08:39 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/07 14:07:17 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_fdwrite(t_lexer *word, char *cmd, char token, int nb)
{
	char	*file;
	int		clone;
	int		i;

	while (cmd[word->i] == token)
		word->i++;
	while (cmd[word->i] == ' ')
		word->i++;
	clone = word->i;
	i = open_fw_bis(cmd, word, 0);
	word->i = clone;
	file = malloc(sizeof(char) * (i + 1));
	if (file == NULL)
		return (0);
	i = 0;
	file = open_fw_bis2(cmd, word, i, file);
	if (token == '>' && nb == 1)
		clone = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (token == '>' && nb == 2)
		clone = open(file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (token == '<')
		clone = open(file, 0);
	free(file);
	return (clone);
}

int	skip_quots(char *cmd, t_lexer *word)
{
	if (cmd[word->i] == '\"')
	{
		word->i++;
		while (cmd[word->i] != '\"')
		{
			if (cmd[word->i] == '\0')
				return (0);
			word->i++;
		}
	}
	if (cmd[word->i] == '\'')
	{
		word->i++;
		while (cmd[word->i] != '\'')
		{
			if (cmd[word->i] == '\0')
				return (0);
			word->i++;
		}
	}
	return (1);
}

int	search_for_fdwrite(t_lexer *word, char *cmd, int start)
{
	word->i = start;
	while (cmd[word->i] != '\0' && cmd[word->i] != '|')
	{
		if (skip_quots(cmd, word) == 0)
			return (0);
		if (cmd[word->i] == '>')
		{
			if (cmd[word->i + 1] == '>')
				word->fdwrite = open_fdwrite(word, cmd, '>', 2);
			else
				word->fdwrite = open_fdwrite(word, cmd, '>', 1);
			if (word->fdwrite == -1)
				return (0);
		}
		if (cmd[word->i] != '\0' && cmd[word->i] != '|')
			word->i++;
	}
	return (1);
}

int	search_for_fdread(t_lexer *word, char *cmd, int start)
{
	word->i = start;
	while (cmd[word->i] && cmd[word->i] != '|')
	{
		if (!skip_quots(cmd, word))
			return (0);
		if (cmd[word->i] == '<')
		{
			if (cmd[word->i + 1] == '<' && !ft_double(cmd))
				return (0);
			else if (cmd[word->i + 1] != '<')
			{
				word->fdread = open_fdwrite(word, cmd, '<', 0);
				if (word->fdread == -1 || dup2(word->fdread, STDIN_FILENO) < 0)
					return (0);
				word->i--;
			}
			else
				word->i++;
		}
		word->i++;
	}
	return (1);
}
