#include "minishell.h"

int open_fw_bis(char *cmd, lexer *word, int i)
{
	while (cmd[word->i] != ' ' && cmd[word->i] != '<' && cmd[word->i] != '>' && cmd[word->i] != '|' && cmd[word->i] != '\0')
	{
		if(cmd[word->i] != '\"' && cmd[word->i] != '\'')
			i++;
		word->i++;
	}
	return (i);
}

char	*open_fw_bis2(char *cmd, lexer *word, int i, char *file)
{
	while (cmd[word->i] != ' ' && cmd[word->i] != '<'
		&& cmd[word->i] != '>' && cmd[word->i] != '|'
		&& cmd[word->i] != '\0')
	{
		if(cmd[word->i] != '\"' && cmd[word->i] != '\'')
		{
			file[i] = cmd[word->i];
			i++;
		}
		word->i++;
	}
	file[i] = '\0';
	return (file);
}

int open_fdwrite(lexer *word, char *cmd, char token, int nb)
{
	char	*file;
	int clone;
	int i;

	while (cmd[word->i] == token)
		word->i++;
	while (cmd[word->i] == ' ')
		word->i++;
	clone = word->i;
	i = open_fw_bis(cmd, word, 0);
	word->i = clone;
	file = malloc(sizeof(char) * (i + 1));
	if (file == NULL)
		return (0);
	i = 0;
	file = open_fw_bis2(cmd, word, i, file);
	if (token == '>' && nb == 1)
		clone = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (token == '>' && nb == 2)
		clone = open(file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (token == '<')
		clone = open(file, 0);	
	free(file);
	return (clone);
}

int skip_quots(char *cmd, lexer *word)
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
	return (1);
}

int	search_for_fdwrite(lexer *word, char *cmd, int start)
{
	//printf("-> search_for_fdwrite...\n");
	word->i = start;
	while (cmd[word->i] != '\0' && cmd[word->i] != '|')
	{
		if (skip_quots(cmd, word) == 0)
			return (0);
		if (cmd[word->i] == '>')
		{	
			if(cmd[word->i + 1] == '>')
				word->fdwrite = open_fdwrite(word, cmd, '>', 2);
			else
				word->fdwrite = open_fdwrite(word, cmd, '>', 1);
			if (word->fdwrite == -1)
				return (0);
		}
		if (cmd[word->i] != '\0' && cmd[word->i] != '|')
			word->i++;
	}
	return (1);
}

int search_for_fdread(lexer *word, char *cmd, int start)
{
	//printf("-> search_for_fdread...\n");
	word->i = start;
	while (cmd[word->i] != '\0' && cmd[word->i] != '|')
	{
		if (skip_quots(cmd, word) == 0)
			return (0);
		if (cmd[word->i] == '<')
		{
			if (cmd[word->i + 1] == '<')
			{
				if (ft_double(cmd) == 0)
					return (0);
				word->i++;
			}
			else
			{
				word->fdread = open_fdwrite(word, cmd, '<', 0);
				if (word->fdread == -1)
					return (0);
				if (dup2(word->fdread, STDIN_FILENO) < 0)
					return (0);
			}
		}
		word->i++;
	}
	return (1);
}