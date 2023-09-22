#include "minishell.h"

/*lexer	*find_word(lexer *last_word, int i)
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
}*/

/*int skip_from_until(lexer *word, char *cmd, char that, char this)
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
}*/

/*int open_fdwrite(lexer *word, char *cmd, char token)
{
	char	*file;
	int clone;
	int i;

	i = 0;
	while (cmd[word->i] == token)
		word->i++;
	clone = word->i;
	while (cmd[word->i] != ' ' && cmd[word->i] != '<' && cmd[word->i] != '>' && cmd[word->i] != '|' && cmd[word->i] != '\0')
	{
		if(cmd[word->i] != '\"' && cmd[word->i] != '\'')
			i++;
		word->i++;
	}
	word->i = clone;
	file = malloc(sizeof(char) * (i + 1));
	if (file == NULL)
		return (0);
	i = 0;
	while (cmd[word->i] != ' ' && cmd[word->i] != '<' && cmd[word->i] != '>' && cmd[word->i] != '|' && cmd[word->i] != '\0')
	{
		if(cmd[word->i] != '\"' && cmd[word->i] != '\'')
		{
			file[i] = cmd[word->i];
			i++;
		}
		word->i++;
	}
	file[i] = '\0';
	if (token == '>')
		clone = open(file, O_CREAT, 0777);
	if (token == '<')
		clone = open(file, 0);	
	free(file);
	return (clone);
}

int	search_for_fdwrite(lexer *word, char *cmd, int start)
{
	word->i = start;
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
			word->fdwrite = open_fdwrite(word, cmd, '>');
			if (word->fdwrite == -1)
				return (0);
		}
		if (cmd[word->i] != '\0' && cmd[word->i] != '|')
			word->i++;
	}
	return (1);
}

int	search_for_fdread(lexer *word, char *cmd, int start)
{
	word->i = start;
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
			word->fdread = open_fdwrite(word, cmd, '<');
			if (word->fdread == -1)
				return (0);
		}
		word->i++;
	}
	return (1);
}*/

/*int	how_many_arg(char *cmd, int i_bis, int j)
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
}*/

/*int	cmd_in_struct(lexer *word, char *cmd, int start)
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
		else if (cmd[word->i] != ' ' && cmd[word->i] != '\0' && cmd[word->i] != '|' && cmd[word->i] != '\"'  && cmd[word->i] != '\'' && cmd[word->i] != '<' && cmd[word->i] != '>' && word->cmd_check != 0)
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
			}
		}
		else
			word->i++;
	}
	return (-1);
}*/

/*void	ft_free_lexer(lexer *word, char *cmd)
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
}*/

/*void    execute_echo(char **args)
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
}*/

/*int ft_len_of_$(char *str1)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	while (str1[i] != '\0')
	{
		if(str1[i] == '$')
		{
			i++;
			while(str1[i] != ' ' && str1[i] != '\0' && str1[i] != '"' && str1[i] != '|' && str1[i] != '<' && str1[i] != '>' && str1[i] != '$')
			{
				b++;
				i++;
			}
			return (b);
		}
		i++;
	}
	return (b);
}

char	*ft_strinsert(char *str1, char *str2, int pos)
{
	char	*final;
	int		len;
	int		i;
	int		j;
	int		k;

	if (str2 == NULL)
		return (NULL);
	len = ft_strlen(str1) + ft_strlen(str2) - ft_len_of_$(str1);
	final = malloc (sizeof(char) * (len) + 1);
	if (final == NULL)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while(i != len)
	{
		if (i != pos)
		{
			final[i] = str1[j];
			j++;
			i++;
		}
		else
		{
			j++;
			while (str2[k] != '\0')
			{
				final[i] = str2[k];
				k++;
				i++;
			}
			while (str1[j] != ' ' && str1[j] != '\0' && str1[j] != '"' && str1[j] != '|' && str1[j] != '<' && str1[j] != '>' && str1[j] != '$')
				j++;
		}
	}
	free (str1);
	final[i] = '\0';
	return (final);
}

size_t	ft_strlen_space(const char *s, size_t i)
{
	while (s[i] != ' ' && s[i] != '\0' && s[i] != '|' && s[i] != '<' && s[i] != '>' && s[i] != '$')
		i++;
	return (i);
}

char	*search_for_env(lexer *word, char *cmd, int start)
{
	char	*str2;
	int		i;
	int		j;

	word->i = start;
	while (cmd[word->i] != '\0' && cmd[word->i] != '|')
	{
		i = 0;
		if (cmd[word->i] == '\'')
		{
			word->i++;
			while (cmd[word->i] != '\'')
			{
				if (cmd[word->i] == '\0')
					return (NULL);
				word->i++;
			}
		}
		if (cmd[word->i] == '$' && cmd[word->i + 1] == '?')
			word->i = word->i + 2;
		if (cmd[word->i] == '$')
		{
			word->i++;
			j = word->i;
			str2 = malloc(sizeof(char) * (ft_strlen_space(cmd, word->i) + 1));
			while (cmd[j] != '\0' && cmd[j] != ' ' && cmd[j] != '"' && cmd[j] != '|' && cmd[j] != '<' && cmd[j] != '>' && cmd[j] != '$')
			{
				str2[i] = cmd[j];
				i++;
				j++;
			}
			str2[i] = '\0';
			cmd = ft_strinsert(cmd, getenv(str2), word->i - 1);
			if (cmd == NULL)
				return (NULL);
		}
		word->i++;
	}
	//free (str2);
	return (cmd);
}*/

/*void  INThandler(int sig)
{
	if (sig == SIGSEGV)
	{
		printf("\nYou press Ctrl-D\n");
		exit(1);
	}
	else if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		(void) sig;
	}
	else
		printf("\n Sorry... What ??\n");
}*/

int nbr_of_pipe(char *cmd)
{
	int t;
	int i;

	t = 1;
	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\"')
		{
			i++;
			while(cmd[i] != '\"' && cmd [i] != '\0')
				i++;
		}
		else if (cmd[i] == '\'')
		{
			i++;
			while(cmd[i] != '\'' && cmd [i] != '\0')
				i++;
		}
		else if (cmd[i] == '|')
			t++;
		if(cmd[i] != '\0')
			i++;
	}
	return (t);
}

char	*env_write_read(char *cmd, lexer *word, int start)
{
//Remplace les $ par l'environnement
	word->good = 1;
	cmd = search_for_env(word, cmd, start);
	if (cmd == NULL)
	{
		printf("We got a problem with the environnement bro !\n");
		word->good = 0;
	}
	printf("   Environnement done !\n");
//Recherche pour fdread.
	if (word->good == 1 && search_for_fdread(word, cmd, start) == 0)
	{
		printf("We got a problem with fdread bro !\n");
		word->good = 0;
	}
	printf("   Fdread done !\n");
//Recherche pour fdwrite.
	if (word->good == 1 && search_for_fdwrite(word, cmd, start) == 0)
	{
		printf("We got a problem with fdwrite bro !\n");
		word->good = 0;
	}
	printf("   Fdwrite done !\n");
	return (cmd);
}

int	last_check(char *cmd, lexer *word, int start, int is_pipe)
{
//Last check across the cmd
	is_pipe = cmd_in_struct(word, cmd, start);
	if (is_pipe == 0)
	{
		printf("We got a problem with the struct bro !\n");
		word->good = 0;
		return (0);
	}
	printf("Last_check done !\n");
	return (is_pipe);
}


void main_while(char *cmd, lexer *word, lexer *save, int start)
{
	int		t;
	char		oldpwd[1024];
	char		**environ_copy;
	extern char 		**environ;
	int		i;/* <--- utile pour les print, donc à supprimer */
	int		j;/* <--- utile pour les print, donc à supprimer */

	t = nbr_of_pipe(cmd);
	j = t; /* <--- utile pour les print, donc à supprimer */
	i = 0;/* <--- utile pour les print, donc à supprimer */
	while (t != 0)
	{
		word = struct_init(word, t);
		t--;
		i++;
	}
	t = 1;
	while (t > 0)
	{
		cmd = env_write_read(cmd, word, start);
		if (word->good == 1)
		{
			t = last_check(cmd, word, start, t);
			if (t > 0)
			{
				printf("WE FIND A PIPE ! ABOOOOORT MISSION !\n"); /* <--- à supprimer */
				start = t + 1;
				save = word;
				word = word->next;
				word->prev = save;
			}
		}
		else
			t = 0;
	}

	if (word->good == 1)
	{
		printf("\n   RESULTAT !!!\n\n");
		/*LES FONCTION QUI FONT PARTIE DE L'EXECUTION DOIVENT ÊTRE MISENT CI DESSOUS
			   |XX|
			   |XX|
			   |XX|
			 \XXXXXX/
		 	  \XXXX/
			   \XX/
		        \/		*/

		environ_copy = duplicate_environ(environ);

		if (word->word == NULL)
		{
			t++;
			t--;
		}

		else if (strcmp(word->word, "echo") == 0)
		{
			execute_echo(&word->arg[-1]);
			//continue ;
		}

		else if (strcmp(word->word, "cd") == 0)
		{
			execute_cd(&word->arg[-1], oldpwd);
			//continue ;
		}

		else if (strcmp(word->word, "pwd") == 0)
		{
			execute_pwd();
			//continue ;
		}

		else if (strcmp(word->word, "export") == 0)
		{
			execute_export(&word->arg[-1], &environ_copy);
			//continue ;
		}

		else if (strcmp(word->word, "unset") == 0)
		{
			execute_unset(&word->arg[-1], &environ);
			//continue ;
		}

		else if (strcmp(word->word, "env") == 0)
		{
			execute_env(environ);
			//continue ;
		}

		else if (strcmp(word->word, "exit") == 0)
		{
			execute_exit(&word->arg[-1]);
		}

		/*      /\ 
			   /XX\ 
		 	  /XXXX\		
			 /XXXXXX\ 
			   |XX|
			   |XX|
			   |XX|
		LES FONCTION QUI FONT PARTIE DE L'EXECUTION DOIVENT ÊTRE MISENT CI DESSUS*/
		printf("\n   FIN DES RESULTAT !!!\n");
	}
	//Ici on close le fdwrite. Ceci n'est pour le moment utile qu'au lexer-parser, donc se référer à Zalius, à supprimer ???
		if (word->fdwrite != 0)
			close(word->fdwrite);
		if (word->fdread != 0)
			close(word->fdread);

	//Ici on imprime une serie d'élément afin de checker que tout fonctionne, à supprimer. ATTENTION, CECI MODIFIE LES VALEURS !!!
	if (word->good == 1)
	{
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
	}

	//Ici on Free tout le lexer.
	ft_free_lexer(word, cmd);
	printf("\n    -- END OF LOOP --\n\n\n");
}

int main(void)
{
	char		*cmd;
	//char	**cmd_list;
	//int		t;
	//int		i;/* <--- utile pour les print, donc à supprimer */1]
	//int		j;/* <--- utile pour les print, donc à supprimer */
	int			start;
	lexer		*word;
	lexer		*save;

	signal(SIGSEGV, INThandler);
	signal(SIGINT, INThandler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		cmd = readline("Prompt > ");
		add_history(cmd);
		word = NULL;
		save = NULL;
		start = 0;
		main_while(cmd, word, save, start);
	}
	return (0);
}

//save validé yeeee !