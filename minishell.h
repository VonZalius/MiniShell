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

typedef struct mini mini;
struct mini
{
	char	*final;
	int		len;
	int		i;
	int		j;
	int		k;
};

typedef struct lexer lexer;
struct lexer
{
	int		quot_check;
	int		cmd_check;
    int		index;
	int		i;
	int		good;
	char	*word;
	char	**arg;
	int		fdread;
	int		fdwrite;
	int		fdpipe;
    lexer	*next;
	lexer	*prev;
};

int		search_for_fdread(lexer *word, char *cmd, int start);
int		search_for_fdwrite(lexer *word, char *cmd, int start);
char	*search_for_env(lexer *word, char *cmd, int start);
lexer	*struct_init(lexer *prevew, int i);
lexer	*find_word(lexer *last_word, int i);
int		cmd_in_struct(lexer *word, char *cmd, int start);
int		how_many_arg(char *cmd, int i_bis, int j);
int 	skip_from_until(lexer *word, char *cmd, char that, char this);
void	ft_free_lexer(lexer *word, char *cmd);
void	INThandler(int sig);
void	rl_replace_line(const char *text, int clear_undo);
void	ft_other(lexer *word, char **environ);
char	*ft_strinsert_fd(char *str1, char *str2, int pos);
int	ft_double(char *cmd);
char *ft_strcat(char *dest, char *src);


#endif