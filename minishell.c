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
	while (cmd[i_bis] != '\0' && cmd[i_bis] != '|')
	{
		if (cmd[i_bis] == '\"')
		{
			i_bis++;
			while (cmd[i_bis] != '\"')
				i_bis++;
			j++;
		}
		else if (cmd[i_bis] == '\'')
		{
			i_bis++;
			while (cmd[i_bis] != '\'')
				i_bis++;
			j++;
		}
		else if (cmd[i_bis] == '-')
			j++;
		i_bis++;
	}
	return (j);
}

int	cmd_in_struct(lexer *word, char *cmd, int start)
{
	int		i_bis;
	int		j;
	int		index_arg;
	int		cmd_check;

	word->i = start;
	index_arg = 0;
	i_bis = 0;
	j = 0;
	j = how_many_arg(cmd, start, j);
	word->arg = (char **)malloc(sizeof(char *) * j + 1);
	if (word->arg == NULL)
		return (0);
	cmd_check = 0;
	while (cmd[word->i] != '\0')
	{
		i_bis = word->i;
		if (cmd[word->i] == '|')
			return (word->i);
		//skip_from_until(word, cmd, '<', ' ');
		//skip_from_until(word, cmd, '>', ' ');
		if (cmd[word->i] == ' ')
		{
			while (cmd[word->i] == ' ')
				word->i++;
		}
		else if (cmd[word->i] == '<' || cmd[word->i] == '>')
		{
			word->i++;
			while(cmd[word->i] != ' ' && cmd[word->i] != '\0' && cmd[word->i] != '|' && cmd[word->i] != '-' && cmd[word->i] != '<' && cmd[word->i] != '>' && cmd[word->i] != '\'' && cmd[word->i] != '\"')
				word->i++;
		}
		else if (cmd[word->i] == '-')
		{
			word->i++;
			i_bis++;
			while (cmd[i_bis] != ' ' && cmd[i_bis] != '\0' && cmd[i_bis] != '|' && cmd[i_bis] != '-' && cmd[i_bis] != '\"'  && cmd[i_bis] != '\'' && cmd[i_bis] != '<' && cmd[i_bis] != '>')
				i_bis++;
			word->arg[index_arg] = malloc(sizeof(char) * i_bis - word->i + 1);
			if (word->arg[index_arg] == NULL)
				return (0);
			i_bis = 0;
			while (cmd[word->i] != ' ' && cmd[word->i] != '\0' && cmd[word->i] != '|' && cmd[word->i] != '-' && cmd[word->i] != '<' && cmd[word->i] != '>' && cmd[word->i] != '\'' && cmd[word->i] != '\"')
			{
				word->arg[index_arg][i_bis] = cmd[word->i];
				word->i++;
				i_bis++;
			}
			word->arg[index_arg][i_bis] = '\0';
			index_arg++;
		}
		else if (cmd[word->i] == '\"')
		{
			i_bis++;
			while (cmd[i_bis] != '\"')
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
		else if (cmd[word->i] == '\'')
		{
			i_bis++;
			while (cmd[i_bis] != '\'')
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
			if (cmd_check == 1)
			{
				printf("To many commands\n");
				return (0);
			}
			while (cmd[i_bis] != ' ' && cmd[i_bis] != '\0' && cmd[i_bis] != '|' && cmd[i_bis] != '-' && cmd[i_bis] != '"'  && cmd[i_bis] != '\'' && cmd[i_bis] != '<' && cmd[i_bis] != '>')
				i_bis++;
			word->word = malloc(sizeof(char) * i_bis - word->i + 1);
			if (word->word == NULL)
				return (0);
			i_bis = 0;
			while (cmd[word->i] != ' ' && cmd[word->i] != '\0' && cmd[word->i] != '|' && cmd[word->i] != '-' && cmd[word->i] != '<' && cmd[word->i] != '>' && cmd[word->i] != '\'' && cmd[word->i] != '\"')
			{
				word->word[i_bis] = cmd[word->i];
				word->i++;
				i_bis++;
			}
			word->word[i_bis] = '\0';
			cmd_check = 1;
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

		//Ici on imprime dans le terminal divers élément afin de tester ce que réalise le reste du programme.
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
			while (t < how_many_arg(cmd, i, 0))
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

//save validé !