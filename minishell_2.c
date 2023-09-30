/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:16:42 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/28 14:52:58 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*env_write_read(char *cmd, t_lexer *word, int start)
{
//Remplace les $ par l'environnement
	if (word->good == 1)
		cmd = search_for_env(word, cmd, start);
	if (word->good == 1 && cmd == NULL)
	{
		printf("We got a problem with the environnement bro !\n");
		word->good = 0;
	}
	//printf("   Environnement done !\n");
//Recherche pour fdread.
	if (word->good == 1 && search_for_fdread(word, cmd, start) == 0)
	{
		printf("We got a problem with fdread bro !\n");
		word->good = 0;
	}
	//printf("   Fdread done !\n");
//Recherche pour fdwrite.
	if (word->good == 1 && search_for_fdwrite(word, cmd, start) == 0)
	{
		printf("We got a problem with fdwrite bro !\n");
		word->good = 0;
	}
	//printf("   Fdwrite done !\n");
//Remplace les $ par l'environnement
	if (word->good == 1)
		cmd = search_for_env(word, cmd, start);
	if (word->good == 1 && cmd == NULL)
	{
		printf("We got a problem with the environnement bro !\n");
		word->good = 0;
	}
	//printf("   Environnement done !\n");
	return (cmd);
}

int	last_check(char *cmd, t_lexer *word, int start, int is_pipe)
{
//Last check across the cmd
	is_pipe = cmd_in_struct(word, cmd, start);
	if (is_pipe == 0)
	{
		printf("We got a problem with the struct bro !\n");
		word->good = 0;
		return (0);
	}
	//printf("Last_check done !\n");
	return (is_pipe);
}

void executor_2(t_lexer *word, char **environ, int saved_stdout)
{
	if (word->fdwrite > 1)
		if (dup2(word->fdwrite, STDOUT_FILENO) < 0)
			word->good = 0;
	if (word->good != 0)
		ft_other(word, environ);
	//Ici on reboot tout les entrée et sortie standart
	if (word->fdwrite > 1)
		dup2(saved_stdout, STDOUT_FILENO);
	//close(saved_stdout);
}

void	executor(t_lexer *word, int saved_stdout, int t)
{
	char		oldpwd[1024];
	extern char	**environ;
	int			last_command_status = 0;

	if (word->good == 1)
	{
		//printf("\n   RESULTAT !!!\n\n");
		/*LES FONCTION QUI FONT PARTIE DE L'EXECUTION DOIVENT ÊTRE MISENT CI DESSOUS
			   |XX|
			   |XX|
			   |XX|
			 \XXXXXX/
		 	  \XXXX/
			   \XX/
		        \/		*/


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
			word->dol = execute_exit(&word->arg[-1],last_command_status);
	//Execution commande de base (j'imagine)
		else
			executor_2(word, environ, saved_stdout);

		/*      /\
			   /XX\
		 	  /XXXX\
			 /XXXXXX\
			   |XX|
			   |XX|
			   |XX|
		LES FONCTION QUI FONT PARTIE DE L'EXECUTION DOIVENT ÊTRE MISENT CI DESSUS*/
		//printf("\n   FIN DES RESULTAT !!!\n");
	}
}