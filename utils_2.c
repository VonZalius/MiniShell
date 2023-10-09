/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:55:49 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/05 00:56:18 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup(t_lexer *word)
{
	int	i;

	i = 0;
	if (word->arg)
	{
		while (word->arg[i])
		{
			free(word->arg[i]);
			i++;
		}
		free(word->arg);
	}
	if (word->word)
		free(word->word);
	free(word);
}

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

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_close_handler(void)
{
	int	j;

	j = open("/Users/abarras/gittest/pipe_handler",
			O_RDWR | O_TRUNC | O_CREAT, 0644);
	close(j);
	j = open("/Users/abarras/gittest/pdouble_handler",
			O_RDWR | O_TRUNC | O_CREAT, 0644);
	close(j);
	j = open("/Users/abarras/gittest/pipe_handler_2",
			O_RDWR | O_TRUNC | O_CREAT, 0644);
	close(j);
}
