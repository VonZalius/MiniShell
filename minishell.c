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


int	fd_for_pipe(t_lexer *word)
{
	int fichier_sortie;

	fichier_sortie = open("pipe_handler", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fichier_sortie == -1)
		return (0);
	word->fdwrite = fichier_sortie;
	return (1);
}

int insert_for_pipe_2(char *buffer, t_lexer *word)
{
	int	i;
	int fichier_entree;

	fichier_entree = open("pipe_handler_2", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fichier_entree == -1)
	{
		free(buffer);
		return (0);
	}
	word->fdread = fichier_entree;
	i = 0;
	while(buffer[i] != '\0')
	{
		write(word->fdread, &buffer[i], 1);
		i++;
	}
	free (buffer);
	close(word->fdread);
	fichier_entree = open("pipe_handler_2", 0);
	if (fichier_entree == -1)
		return (0);
	if (dup2(word->fdread, STDIN_FILENO) < 0)
		return (0);
	return (1);
}

int	insert_for_pipe(t_lexer *word)
{
	char *buffer;
	int bytes_read;
	int	fd;

	fd = open("pipe_handler", 0);
	if (fd < 0)
		return (0);
	buffer = malloc(sizeof(char) * 1024);
	bytes_read = read(fd, buffer, 1024);
	buffer[bytes_read - 1] = '\0';
	close(fd);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (0);
	}
	if (insert_for_pipe_2(buffer, word) == 0)
		return (0);
	return (1);
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

int	executor(t_lexer *word, int saved_stdout, int t)
{
	char		oldpwd[1024];
	extern char	**environ;
	int			return_value;
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
			return_value = execute_echo(&word->arg[-1], word->fdwrite);
		else if (ft_strcmp(word->word, "cd") == 0)
			return_value = execute_cd(&word->arg[-1], oldpwd);
		else if (ft_strcmp(word->word, "pwd") == 0)
			return_value = execute_pwd(word->fdwrite);
		else if (ft_strcmp(word->word, "export") == 0)
			return_value = execute_export(&word->arg[-1], &environ, word->fdwrite);
		else if (ft_strcmp(word->word, "unset") == 0)
			return_value = execute_unset(&word->arg[-1], &environ);
		else if (ft_strcmp(word->word, "env") == 0)
			return_value = execute_env(environ, word->fdwrite);
		else if (ft_strcmp(word->word, "exit") == 0)
			return_value = execute_exit(&word->arg[-1],last_command_status);
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
	return (return_value);
}

void pipe_init(t_lexer *word)
{
	word->good = 1;
	//Ici on initialise l'entrée qui suit le pipe
	if (word->good == 1)
		if (word->fdpipe != 0 && word->good == 1)
			if(insert_for_pipe(word) == 0)
				word->good = 0;
}

void pipe_out(t_lexer *word, int t)
{
//Ici on change la sortie en cas de pipe
	if (word->good == 1)
	{
		if (t > 0)
			if (fd_for_pipe(word) == 0)
				word->good = 0;
		//printf("   Exit pipe initialized !\n");
	}
}

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

t_lexer	*struct_pipe(t_lexer *word, t_lexer *save)
{
	close(word->fdwrite);
	save = word;
	word = word->next;
	word->prev = save;
	word->fdpipe = 1;
	return (word);
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

	t = nbr_of_pipe(cmd);
	//j = t; /* <--- utile pour les print, donc à supprimer */
	//i = 0;/* <--- utile pour les print, donc à supprimer */

	//Ici on initialise les Structures
	while (t != 0)
	{
		word = struct_init(word, t);
		t--;
		//i++;/* <--- utile pour les print, donc à supprimer */
	}
	t = 1;
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
