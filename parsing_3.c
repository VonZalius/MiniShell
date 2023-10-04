/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 00:50:05 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/05 01:24:12 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
