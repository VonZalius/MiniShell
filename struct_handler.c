/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:20:48 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/05 00:52:18 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*find_word(t_lexer *last_word, int i)
{
	if (last_word->index == i)
		return (last_word);
	return (find_word(last_word->prev, i));
}

t_lexer	*struct_init(t_lexer *prevew, int i, int m)
{
	t_lexer	*lexer_word;

	lexer_word = malloc(sizeof(*lexer_word));
	if (lexer_word == NULL)
		return (NULL);
	lexer_word->i = 0;
	lexer_word->fdread = 0;
	lexer_word->fdwrite = 0;
	lexer_word->fdpipe = 0;
	lexer_word->arg = NULL;
	lexer_word->index = i;
	lexer_word->word = NULL;
	lexer_word->next = prevew;
	lexer_word->prev = NULL;
	lexer_word->free_check = 0;
	lexer_word->dol = m;
	lexer_word->good = 1;
	return (lexer_word);
}
