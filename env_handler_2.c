/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:53:38 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/28 12:57:23 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char	*dollar()
{
	char	*buffer;
	int		bytes_read;
	int		fd;

	fd = open("pipe_handler", 0);
	if (fd < 0)
		return (NULL);
	buffer = malloc(sizeof(char) * 1024);
	bytes_read = read(fd, buffer, 1024);
	buffer[bytes_read] = '\0';
	close(fd);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}*/

char    *dollar_search(char *cmd, t_lexer *word)
{
    /*char	*ddollar;

	ddollar = dollar();
	if (ddollar == NULL)
		return (NULL);
	cmd = ft_strinsert(cmd, ddollar, word->i);
	free (ddollar);*/

    int i;

    i = 0;
    cmd = ft_strinsert(cmd, ft_itoa(i), word->i);
    return (cmd);
}