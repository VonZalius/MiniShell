/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:01:40 by cmansey           #+#    #+#             */
/*   Updated: 2023/08/07 17:40:36 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	execute_pwd(int fd)
{
	char	cwd[1024];
	int		j;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("pwd");
		return ;
	}


	j = 0;
	while(cwd[j])
	{
		write(fd, &cwd[j], 1);
		j++;
	}
	write(fd, "\n", 1);
	//printf("%s\n", cwd);
}
