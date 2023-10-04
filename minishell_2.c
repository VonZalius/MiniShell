/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:16:42 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/05 00:48:35 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_of_pipe(char *cmd)
{
	int	t;
	int	i;

	t = 1;
	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"' && cmd [i] != '\0')
				i++;
		}
		else if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'' && cmd [i] != '\0')
				i++;
		}
		else if (cmd[i] == '|')
			t++;
		if (cmd[i] != '\0')
			i++;
	}
	return (t);
}

//Remplace les $ par l'environnement
//Recherche pour fdread.
//Recherche pour fdwrite.
char	*env_write_read(char *cmd, t_lexer *word, int start)
{
	if (word->good == 1)
		cmd = search_for_env(word, cmd, start);
	if (word->good == 1 && cmd == NULL)
	{
		printf("We got a problem with the environnement bro !\n");
		word->good = 0;
	}
	if (word->good == 1 && search_for_fdread(word, cmd, start) == 0)
	{
		printf("We got a problem with reading bro !\n");
		word->good = 0;
	}
	if (word->good == 1 && search_for_fdwrite(word, cmd, start) == 0)
	{
		printf("We got a problem with writing bro !\n");
		word->good = 0;
	}
	if (word->good == 1)
		cmd = search_for_env(word, cmd, start);
	if (word->good == 1 && cmd == NULL)
	{
		printf("We got a problem with the environnement bro !\n");
		word->good = 0;
	}
	return (cmd);
}

int	last_check(char *cmd, t_lexer *word, int start, int is_pipe)
{
	is_pipe = cmd_in_struct(word, cmd, start);
	if (is_pipe == 0)
	{
		printf("We got a problem with the struct bro !\n");
		word->good = 0;
		return (0);
	}
	return (is_pipe);
}

//Ici on reboot tout les entrée et sortie standart
void	executor_2(t_lexer *word, char **environ, int saved_stdout, char *cmd)
{
	g_signal = 1;
	if (word->fdwrite > 1)
		if (dup2(word->fdwrite, STDOUT_FILENO) < 0)
			word->good = 0;
	if (word->good != 0)
		ft_other(word, environ, cmd);
	if (word->fdwrite > 1)
		dup2(saved_stdout, STDOUT_FILENO);
	g_signal = 0;
}

void	executor(t_lexer *word, int saved_stdout, int t, char *cmd)
{
	char		oldpwd[1024];
	extern char	**environ;

	if (word->good == 1)
	{
		if (word->word == NULL)
			t++;
		else if (ft_strcmp(word->word, "echo") == 0)
			word->dol = execute_echo(&word->arg[-1], word->fdwrite);
		else if (ft_strcmp(word->word, "cd") == 0)
			word->dol = execute_cd(&word->arg[-1], oldpwd);
		else if (ft_strcmp(word->word, "pwd") == 0)
			word->dol = execute_pwd(word->fdwrite);
		else if (ft_strcmp(word->word, "export") == 0)
			word->dol = execute_export(&word->arg[-1], &environ, word->fdwrite);
		else if (ft_strcmp(word->word, "unset") == 0)
			word->dol = execute_unset(&word->arg[-1], &environ);
		else if (ft_strcmp(word->word, "env") == 0)
			word->dol = execute_env(environ, word->fdwrite);
		else if (ft_strcmp(word->word, "exit") == 0)
			word->dol = execute_exit(word, &word->arg[-1]);
		else
			executor_2(word, environ, saved_stdout, cmd);
	}
}
