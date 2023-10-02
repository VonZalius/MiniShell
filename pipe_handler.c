/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:16:42 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/01 18:40:38 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fd_for_pipe(t_lexer *word)
{
	int	fichier_sortie;

	fichier_sortie = open("pipe_handler", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fichier_sortie == -1)
		return (0);
	word->fdwrite = fichier_sortie;
	return (1);
}

int	insert_for_pipe_2(char *buffer, t_lexer *word)
{
	int	i;
	int	fichier_entree;

	fichier_entree = open("pipe_handler_2", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fichier_entree == -1)
	{
		free(buffer);
		return (0);
	}
	word->fdread = fichier_entree;
	i = 0;
	while (buffer[i] != '\0')
	{
		write(word->fdread, &buffer[i], 1);
		i++;
	}
	write(word->fdread, "\n", 1);
	free (buffer);
	close(word->fdread);
	fichier_entree = open("pipe_handler_2", 0);
	if (fichier_entree == -1)
		return (0);
	if (dup2(word->fdread, STDIN_FILENO) < 0)
		return (0);
	return (1);
}

int	insert_for_pipe(t_lexer *word)
{
	char	*buffer;
	int		bytes_read;
	int		fd;

	fd = open("pipe_handler", 0);
	if (fd < 0)
		return (0);
	buffer = malloc(sizeof(char) * 1024);
	bytes_read = read(fd, buffer, 1024);
	buffer[bytes_read - 1] = '\0';
	close(fd);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (0);
	}
	if (insert_for_pipe_2(buffer, word) == 0)
		return (0);
	return (1);
}

void	pipe_init(t_lexer *word)
{
	word->good = 1;
	//Ici on initialise l'entrée qui suit le pipe
	if (word->good == 1)
		if (word->fdpipe != 0 && word->good == 1)
			if (insert_for_pipe(word) == 0)
				word->good = 0;
}

void	pipe_out(t_lexer *word, int t)
{
//Ici on change la sortie en cas de pipe
	if (word->good == 1)
	{
		if (t > 0)
			if (fd_for_pipe(word) == 0)
				word->good = 0;
		//printf("   Exit pipe initialized !\n");
	}
}

