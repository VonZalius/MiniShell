#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct lexer lexer;
struct lexer
{
    int		index;
	int		is_token;
	char	*word;
    lexer	*next;
	lexer	*prev;
};

#endif