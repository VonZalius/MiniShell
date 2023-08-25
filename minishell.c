#include "minishell.h"

lexer	*find_word(lexer *last_word, int i)
{
	if(last_word->index == i)
		return(last_word);
	return (find_word(last_word->prev, i));
}

lexer	*struct_init(lexer *prevew, int i)
{
	lexer	*lexer_word;

	lexer_word = malloc(sizeof(*lexer_word));
	if (lexer_word == NULL)
	{
		free(lexer_word);
		return(NULL);
	}
	lexer_word->i = 0;
	lexer_word->fdread = 0;
	lexer_word->fdwrite = 0;
	lexer_word->arg = NULL;
	lexer_word->index = i;
	lexer_word->word = NULL;
	lexer_word->next = prevew;
	lexer_word->prev = NULL;
	return (lexer_word);
}

int skip_from_until(lexer *word, char *cmd, char that, char this)
{
	if (cmd[word->i] == that)
	{
		while (cmd[word->i] == that)
			word->i++;
		while (cmd[word->i] != this)
		{
			if (cmd[word->i] == '\0')
			{
				if (this != ' ')
					printf("There is a -> %c <- missing\n", this);
				return (0);
			}
			if (cmd[word->i] == '\\')
				word->i++;
			word->i++;
		}
	}
	return (1);
}

int	search_for_fdwrite(lexer *word, char *cmd)
{
	word->i = 0;
	while (cmd[word->i] != '\0' && cmd[word->i] != '|')
	{
		if (cmd[word->i] == '\"')
		{
			word->i++;
			while (cmd[word->i] != '\"')
			{
				if (cmd[word->i] == '\0')
					return (0);
				word->i++;
			}
		}
		if (cmd[word->i] == '\'')
		{
			word->i++;
			while (cmd[word->i] != '\'')
			{
				if (cmd[word->i] == '\0')
					return (0);
				word->i++;
			}
		}
		if (cmd[word->i] == '>')
		{
			word->i++;
			if (cmd[word->i] == '>')
			{
				word->fdwrite = 21;
			}
			else
			{
				word->fdwrite = 20;
				word->i--;
			}
		}
		word->i++;
	}
	return (1);
}

int	search_for_fdread(lexer *word, char *cmd)
{
	word->i = 0;
	while (cmd[word->i] != '\0' && cmd[word->i] != '|')
	{
		if (cmd[word->i] == '\"')
		{
			word->i++;
			while (cmd[word->i] != '\"')
			{
				if (cmd[word->i] == '\0')
					return (0);
				word->i++;
			}
		}
		if (cmd[word->i] == '\'')
		{
			word->i++;
			while (cmd[word->i] != '\'')
			{
				if (cmd[word->i] == '\0')
					return (0);
				word->i++;
			}
		}
		if (cmd[word->i] == '<')
		{
			word->i++;
			if (cmd[word->i] == '<')
			{
				word->fdread = 11;
			}
			else
			{
				word->fdread = 10;
				word->i--;
			}
		}
		word->i++;
	}
	return (1);
}

int	how_many_arg(char *cmd, int i_bis, int j)
{
	int	copy;

	copy = i_bis;
	while (cmd[i_bis] != '\0' && cmd[i_bis] != '|')
	{
		if (i_bis == copy && cmd[i_bis] == ' ')
		{
			while (cmd[i_bis] == ' ')
				i_bis++;
		}
		else if (cmd[i_bis] == '\"')
		{
			i_bis++;
			while (cmd[i_bis] != '\"' && cmd[i_bis] != '\0')
				i_bis++;
			i_bis++;
		}
		else if (cmd[i_bis] == '\'')
		{
			i_bis++;
			while (cmd[i_bis] != '\'' && cmd[i_bis] != '\0')
				i_bis++;
			i_bis++;
		}
		else if (cmd[i_bis] == '<' || cmd[i_bis] == '>')
		{
			while (cmd[i_bis] == '<' || cmd[i_bis] == '>')
				i_bis++;
			j--;
		}
		else if (cmd[i_bis] == ' ')
		{
			while (cmd[i_bis] == ' ')
				i_bis++;
			if (cmd[i_bis] == '|' || cmd[i_bis] == '\0')
				return (j);
			if (cmd[i_bis] == '<' || cmd[i_bis] == '>')
			{
				while (cmd[i_bis] == '<' || cmd[i_bis] == '>')
					i_bis++;
				j--;
			}
			j++;
		}
		else
			i_bis++;

	}
	return (j);
}

int	cmd_in_struct(lexer *word, char *cmd, int start)
{
	int			i_bis;
	int			j;
	int			index_arg;

	word->i = start;
	index_arg = 0;
	i_bis = 0;
	j = 0;
	j = how_many_arg(cmd, start, j);
	word->arg = (char **)malloc(sizeof(char *) * (j + 1));
	if (word->arg == NULL)
		return (0);
	word->cmd_check = 0;
	while (cmd[word->i] != '\0')
	{
		i_bis = word->i;
		if (cmd[word->i] == '|')
			return (word->i);
		if (cmd[word->i] == ' ')
		{
			while (cmd[word->i] == ' ')
				word->i++;
		}

		else if (word->cmd_check == 0 && cmd[word->i] != ' ' && cmd[word->i] != '\0' && cmd[word->i] != '|' && cmd[word->i] != '<' && cmd[word->i] != '>')
		{
			while (cmd[i_bis] != ' ' && cmd[i_bis] != '\0' && cmd[i_bis] != '|' && cmd[i_bis] != '<' && cmd[i_bis] != '>')
				i_bis++;
			word->word = malloc(sizeof(char) * i_bis - word->i + 1);
			if (word->word == NULL)
				return (0);
			i_bis = 0;
			while (cmd[word->i] != ' ' && cmd[word->i] != '\0' && cmd[word->i] != '|' && cmd[word->i] != '<' && cmd[word->i] != '>')
			{
				word->word[i_bis] = cmd[word->i];
				word->i++;
				i_bis++;
			}
			word->word[i_bis] = '\0';
			word->cmd_check = 1;
		}

		else if (cmd[word->i] == '<' || cmd[word->i] == '>')
		{
			word->i++;
			while(cmd[word->i] != ' ' && cmd[word->i] != '\0' && cmd[word->i] != '|' && cmd[word->i] != '<' && cmd[word->i] != '>')
				word->i++;
		}
		else if (cmd[word->i] == '-' && word->cmd_check != 0)
		{
			//word->i++;
			//i_bis++;
			while (cmd[i_bis] != ' ' && cmd[i_bis] != '\0' && cmd[i_bis] != '|' && cmd[i_bis] != '<' && cmd[i_bis] != '>')
				i_bis++;
			word->arg[index_arg] = malloc(sizeof(char) * i_bis - word->i + 1);
			if (word->arg[index_arg] == NULL)
				return (0);
			i_bis = 0;
			while (cmd[word->i] != ' ' && cmd[word->i] != '\0' && cmd[word->i] != '|' && cmd[word->i] != '<' && cmd[word->i] != '>')
			{
				word->arg[index_arg][i_bis] = cmd[word->i];
				word->i++;
				i_bis++;
			}
			word->arg[index_arg][i_bis] = '\0';
			index_arg++;
		}
		else if (cmd[word->i] == '\"' && word->cmd_check != 0)
		{
			i_bis++;
			while (cmd[i_bis] != '\"' && cmd[i_bis] != '\0')
				i_bis++;
			word->arg[index_arg] = malloc(sizeof(char) * i_bis - word->i + 1);
			if (word->arg[index_arg] == NULL)
				return (0);
			word->i++;
			i_bis = 0;
			while (cmd[word->i] != '\"')
			{
				word->arg[index_arg][i_bis] = cmd[word->i];
				word->i++;
				i_bis++;
			}
			word->arg[index_arg][i_bis] = '\0';
			word->i++;
			index_arg++;
		}
		else if (cmd[word->i] == '\'' && word->cmd_check != 0)
		{
			i_bis++;
			while (cmd[i_bis] != '\'' && cmd[i_bis] != '\0')
				i_bis++;
			word->arg[index_arg] = malloc(sizeof(char) * i_bis - word->i + 1);
			if (word->arg[index_arg] == NULL)
				return (0);
			word->i++;
			i_bis = 0;
			while (cmd[word->i] != '\'')
			{
				word->arg[index_arg][i_bis] = cmd[word->i];
				word->i++;
				i_bis++;
			}
			word->arg[index_arg][i_bis] = '\0';
			word->i++;
			index_arg++;
		}
		else if (cmd[word->i] != ' ' && cmd[word->i] != '\0' && cmd[word->i] != '|' && cmd[word->i] != '-' && cmd[word->i] != '\"'  && cmd[word->i] != '\'' && cmd[word->i] != '<' && cmd[word->i] != '>')
		{  
			if (word->cmd_check != 0)
			{
				while (cmd[i_bis] != ' ' && cmd[i_bis] != '\0' && cmd[i_bis] != '|' && cmd[i_bis] != '<' && cmd[i_bis] != '>')
					i_bis++;
				word->arg[index_arg] = malloc(sizeof(char) * i_bis - word->i + 1);
				if (word->arg[index_arg] == NULL)
					return (0);
				i_bis = 0;
				while (cmd[word->i] != ' ' && cmd[word->i] != '\0' && cmd[word->i] != '|' && cmd[word->i] != '<' && cmd[word->i] != '>')
				{
					word->arg[index_arg][i_bis] = cmd[word->i];
					word->i++;
					i_bis++;
				}
				word->arg[index_arg][i_bis] = '\0';
				word->i++;
				index_arg++;
				word->cmd_check++;
			}
			/*
			else
			{
				while (cmd[i_bis] != ' ' && cmd[i_bis] != '\0' && cmd[i_bis] != '|' && cmd[i_bis] != '<' && cmd[i_bis] != '>')
					i_bis++;
				word->word = malloc(sizeof(char) * i_bis - word->i + 1);
				if (word->word == NULL)
					return (0);
				i_bis = 0;
				while (cmd[word->i] != ' ' && cmd[word->i] != '\0' && cmd[word->i] != '|' && cmd[word->i] != '<' && cmd[word->i] != '>')
				{
					word->word[i_bis] = cmd[word->i];
					word->i++;
					i_bis++;
				}
				word->word[i_bis] = '\0';
				word->cmd_check = 1;
			}*/
		}
		else
			word->i++;
	}
	return (-1);
}

void	ft_free_lexer(lexer *word, char *cmd)
{
	lexer		*temp;
	int			i;

	while (word != NULL)
	{
		i = 0;
		while (i < how_many_arg(cmd, 0, 0))
		{
			free(word->arg[i]);
			i++;
		}
		free(word->arg);
		if (word->word != NULL)
			free(word->word);
		temp = word;
		word = word->prev;
		free(temp);
	}
	free (cmd);
}

void    execute_echo(char **args)
{
    int    i;
    int    add_newline;

	printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
    i = 1;
    add_newline = 1;
    if (args[1] != NULL && strcmp(args[1], "-n") == 0)
    {
        add_newline = 0;
        i = 2;
    }
    while (args[i] != NULL)
    {
        printf("%s", args[i]);
        if (args[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if (add_newline)
        printf("\n");
}

int main(void)
{
	char	*cmd;
	//char	**cmd_list;
	int		t;
	int		i;
	int		j;
	int		is_pipe;
	int		start;
	lexer		*word;
	lexer		*save;

	while (1)
	{
		cmd = readline("Prompt > ");
		add_history(cmd);
		word = NULL;
		start = 0;
		i = 0;
		t = 1;
		while (cmd[i] != '\0')
		{
			if (cmd[i] == '|')
				t++;
			i++;
		}
		j = t;
		i = 0;
		while (t != 0)
		{
			word = struct_init(word, t);
			t--;
			i++;
		}

		is_pipe = 1;
		while (is_pipe > 0)
		{
		//Recherche pour fdread.
			if (search_for_fdread(word, cmd) == 0)
			{
				printf("We got a problem with fdread bro !\n");
				return (0);
			}
			printf("Fdread done !\n");
		//Recherche pour fdwrite.
			if (search_for_fdwrite(word, cmd) == 0)
			{
				printf("We got a problem with fdwrite bro !\n");
				return (0);
			}
			printf("Fdwrite done !\n");
		//TEST TEST TEST A RECHECKER 	SUPPRIME LES " ET LES '
			
		//Last check across the cmd
			is_pipe = cmd_in_struct(word, cmd, start);
			if (is_pipe == 0)
			{
				printf("We got a problem with the struct bro !\n");
				return (0);
			}
			printf("Last_check done !\n");
			if (is_pipe > 0)
			{
				printf("WE FIND A PIPE ! ABOOOOORT MISSION !\n");
				start = is_pipe + 1;
				save = word;
				word = word->next;
				word->prev = save;
			}
		}

		if (strcmp(word->word, "echo") == 0)
		{
			printf("NIKTARACE");
            execute_echo(word->arg);
            //continue ;
        }

		printf("\nYou said : %s  <--------------------------------------\n\n", cmd);
		j--;
		i = 0;
		word = find_word(word, 1);
		while (j >= 0)
		{
			printf("Struct number %i\n", word->index);
			printf("Word : %s\n", word->word);
			printf("Fdread : %i\n", word->fdread);
			printf("Fdwrite : %i\n", word->fdwrite);
			//printf("howmanyarg : %i\n", how_many_arg(cmd, 0, 0));
			t = 0;
			while (t < (how_many_arg(cmd, i, 0)))
			{
				printf("Arg : %s\n", word->arg[t]);
				t++;
			}
			printf("\n");
			j--;
			word = word->next;
			while (cmd[i] != '|' && cmd[i] != '\0')
				i++;
			i++;
		}
		printf("---------- END ----------\n\n");

		//Ici on Free tout le lexer.
		ft_free_lexer(word, cmd);
	}
	return (0);
}

//save validé (oui oui)!