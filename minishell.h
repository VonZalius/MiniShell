#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct lexer lexer;
struct lexer
{
	int		cmd_check;
    int		index;
	int		i;
	char	*word;
	char	**arg;
	int		fdread;
	int		fdwrite;
    lexer	*next;
	lexer	*prev;
};

#endif