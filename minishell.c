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

void reboot(t_lexer *word, int saved_stdout)
{
//Ici on close le fdwrite. Ceci n'est pour le moment utile qu'au lexer-parser, donc se référer à Zalius, à mettre dans le free_lexer ???
		if (word->fdwrite != 0)
			close(word->fdwrite);
		if (word->fdread != 0)
			close(word->fdread);
	//Ici on reboot tout les entrée et sortie standart
		dup2(saved_stdout, STDOUT_FILENO);
}

int	main_while_2(char *cmd, t_lexer *word, int start, int t)
{
	pipe_init(word);
				//printf("   Enter pipe initialized !\n");
	//Ici on séquence l'input !!
	cmd = env_write_read(cmd, word, start);
	if (word->good == 1)
		t = last_check(cmd, word, start, t);
	else
		t = 0;
	pipe_out(word, t);
	return (t);
}

void main_while(char *cmd, t_lexer *word, t_lexer *save, int start)
{
	int		t;
	//int		i;/* <--- utile pour les print, donc à supprimer */
	//int		j;/* <--- utile pour les print, donc à supprimer */
	int saved_stdin = dup(STDIN_FILENO);
	int saved_stdout = dup(STDOUT_FILENO);
	static int	m;

	t = nbr_of_pipe(cmd);
	//j = t; /* <--- utile pour les print, donc à supprimer */
	//i = 0;/* <--- utile pour les print, donc à supprimer */

	//Ici on initialise les Structures
	while (t != 0)
		word = struct_init(word, t--);
	t = 1;
		word->dol = m;
	while (t > 0)
	{
		t = main_while_2(cmd, word, start, t);
	//Ici on lance l'execution !!!
		executor(word, saved_stdout, t);
		if (t > 0 && word->good == 1)
		{
			//printf("\nWE FIND A PIPE ! ABOOOOORT MISSION ! ----------------------\n\n"); // <--- à supprimer
			start = t + 1;
			word = struct_pipe(word, save);
		}
		reboot(word, saved_stdout);
	}
	m = word->dol;

	//Ici on imprime une serie d'élément afin de checker que tout fonctionne, à supprimer. ATTENTION, CECI MODIFIE LES VALEURS !!!
	/*if (word->good == 1)
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
			t = 0;
			printf("Nbr of Arg = %i\n", how_many_arg(cmd, i, 0));
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
	}*/

	//Ici on Free tout le lexer.
	ft_free_lexer(word, cmd, saved_stdin, saved_stdout);
	//printf("\n    -- END OF LOOP --\n\n\n");
}

int main(void)
{
	char		*cmd;
	int			start;
	t_lexer		*word;
	t_lexer		*save;
	int saved_stdin = dup(STDIN_FILENO);
	int saved_stdout = dup(STDOUT_FILENO);

	signal(SIGSEGV, int_handler);
	signal(SIGINT, int_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		cmd = readline("Prompt > ");
		add_history(cmd);
		word = NULL;
		save = NULL;
		start = 0;
		main_while(cmd, word, save, start);
	}
	return (0);
}
