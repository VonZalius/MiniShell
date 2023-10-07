/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:16:42 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/07 14:03:02 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fin(char *cmd, char *rl)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<' && cmd[i + 1] == '<')
		{
			i += 2;
			while (cmd[i] == ' ')
				i++;
			while (rl[j] != '\0')
			{
				if (cmd[i] != rl[j])
					return (1);
				i++;
				j++;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

char	*ft_strcat_b(char *dest, const char *src)
{
	int		i;
	int		j;
	char	*b;

	i = 0;
	b = malloc (sizeof(char) * 999);
	while (dest[i] != '\0')
	{
		b[i] = dest[i];
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		b[i] = src[j];
		i++;
		j++;
	}
	b[i] = '\0';
	free(dest);
	return (b);
}

int	ft_double_2(char *db2)
{
	int	j;
	int	fd;

	j = 0;
	fd = open("libft/pdouble_handler", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (0);
	while (db2[j])
	{
		write(fd, &db2[j], 1);
		j++;
	}
	free(db2);
	write(fd, "\n", 1);
	close(fd);
	fd = open("libft/pdouble_handler", 0);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (0);
	return (1);
}

int	ft_double(char *cmd)
{
	char	*db;
	char	*db2;
	char	*cmd_copy;

	db = readline("> ");
	db2 = NULL;
	cmd_copy = cmd;
	while (ft_fin(cmd_copy, db))
	{
		if (db2 == NULL)
			db2 = db;
		else
		{
			db2 = ft_strcat_b(db2, "\n\0");
			db2 = ft_strcat_b(db2, db);
		}
		db = NULL;
		db = readline("> ");
	}
	if (ft_double_2(db2) == 0)
		return (0);
	return (1);
}
