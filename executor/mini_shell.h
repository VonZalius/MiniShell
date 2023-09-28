/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:56:54 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/28 12:27:35 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "../libft/libft.h"

# define MAX_INPUT_LENGTH 1024
# define MAX_ARGS 64

void	execute_echo(char **args, int fd);
void	execute_cd(char **args, char *oldpwd);
void	execute_pwd(int fd);
void	execute_export(char **args, char ***environ, int fd);
void	execute_unset(char **args, char ***environ);
void	execute_env(char **environ, int fd);
void	execute_exit(char **args);
void	malloc_error(char **error);
void	malloc_error_1(char *error);
void	free_environ(char **environ);
char	**duplicate_environ(char **environ);
void	write_fd(char *str, int fd);

#endif
