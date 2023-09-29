/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:56:54 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/29 17:38:20 by cmansey          ###   ########.fr       */
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

int		execute_echo(char **args, int fd);
int		execute_cd(char **args, char *oldpwd);
int		execute_pwd(int fd);
int		execute_export(char **args, char ***environ, int fd);
int		execute_unset(char **args, char ***environ);
int		execute_env(char **environ, int fd);
int		execute_exit(char **args, int last_command_status);
void	malloc_error(char **error);
void	malloc_error_1(char *error);
void	free_environ(char **environ);
char	**duplicate_environ(char **environ);
int		write_fd(char *str, int fd);

#endif
