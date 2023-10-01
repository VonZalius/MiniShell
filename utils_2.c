/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:55:49 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/29 17:51:53 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_args(t_lexer *word)
{
	int		i;
	char	**args;

	i = 0;
	while (word->arg[i] != NULL)
		i++;
	args = malloc(sizeof(char *) * (i + 2));
	if (!args)
		return (NULL);
	args[0] = word->word;
	args[1] = word->arg[0];
	args[i + 1] = NULL;
	return (args);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}