/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:20:48 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/28 12:23:24 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*find_word(t_lexer *last_word, int i)
{
	if (last_word->index == i)
		return (last_word);
	return (find_word(last_word->prev, i));
}

t_lexer	*struct_init(t_lexer *prevew, int i)
{
	t_lexer	*lexer_word;

	lexer_word = malloc(sizeof(*lexer_word));
	if (lexer_word == NULL)
	{
		free(lexer_word);
		return (NULL);
	}
	lexer_word->i = 0;
	lexer_word->fdread = 0;
	lexer_word->fdwrite = 0;
	lexer_word->fdpipe = 0;
	lexer_word->arg = NULL;
	lexer_word->index = i;
	lexer_word->word = NULL;
	lexer_word->next = prevew;
	lexer_word->prev = NULL;
	return (lexer_word);
}
