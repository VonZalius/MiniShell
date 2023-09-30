/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:59:54 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/29 16:35:39 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "executor/mini_shell.h"

typedef struct s_mini
{
	char	*final;
	int		len;
	int		i;
	int		j;
	int		k;
}	t_mini;

typedef struct s_lexer
{
	int				dol;
	int				quot_check;
	int				cmd_check;
	int				index;
	int				i;
	int				good;
	char			*word;
	char			**arg;
	int				fdread;
	int				fdwrite;
	int				fdpipe;
	int				error;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

int		search_for_fdread(t_lexer *word, char *cmd, int start);
int		search_for_fdwrite(t_lexer *word, char *cmd, int start);
char	*search_for_env(t_lexer *word, char *cmd, int start);
t_lexer	*struct_init(t_lexer *prevew, int i);
t_lexer	*find_word(t_lexer *last_word, int i);
int		cmd_in_struct(t_lexer *word, char *cmd, int start);
int		how_many_arg(char *cmd, int i_bis, int j);
int		skip_from_until(t_lexer *word, char *cmd, char that, char this);
void	ft_free_lexer(t_lexer *word, char *cmd, int s_stdin, int s_stdout);
void	int_handler(int sig);
void	rl_replace_line(const char *text, int clear_undo);
void	ft_other(t_lexer *word, char **environ);
char	*ft_strinsert_fd(char *str1, char *str2, int pos);
int		ft_double(char *cmd);
char	*ft_strcat(char *dest, const char *src);
void	free_array(char **arr);
char	*ft_strinsert(char *str1, char *str2, int pos);
char	*dollar_search(char *cmd, t_lexer *word);
void	pipe_out(t_lexer *word, int t);
void	pipe_init(t_lexer *word);
t_lexer	*struct_pipe(t_lexer *word, t_lexer *save);
void	executor(t_lexer *word, int saved_stdout, int t);
int		last_check(char *cmd, t_lexer *word, int start, int is_pipe);
char	*env_write_read(char *cmd, t_lexer *word, int start);
int 	nbr_of_pipe(char *cmd);

#endif
