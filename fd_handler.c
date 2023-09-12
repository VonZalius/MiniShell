#include "minishell.h"

int open_fdwrite(lexer *word, char *cmd, char token)
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
}