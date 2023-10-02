/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:01:40 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/02 15:42:39 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_pwd(int fd)
{
	char	cwd[1024];
	int		j;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("pwd");
		return (1);
	}
	j = 0;
	while (cwd[j])
	{
		write(fd, &cwd[j], 1);
		j++;
	}
	write(fd, "\n", 1);
	return (0);
}
