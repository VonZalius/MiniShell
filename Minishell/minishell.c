#include "minishell.h"

lexer	*find_word(lexer *last_word, int i)
{
	if(last_word->index == i)
		return(last_word);
	return (find_word(last_word->prev, i));
}

lexer	*struct_init(char *word, lexer *prevew, int i)
{
	lexer	*lexer_word;

	lexer_word = malloc(sizeof(*lexer_word));
	if (lexer_word == NULL)
		return(NULL);

	lexer_word->index = i;
	lexer_word->word = word;
	lexer_word->next = NULL;
	lexer_word->prev = prevew;
	if (word[0] == '|')
		lexer_word->is_token = 1;
	else
		lexer_word->is_token = 0;
	return (lexer_word);
}

int main(void)
{
	char	*cmd;
	char	**cmd_list;
	int		t;
	int		i;
	lexer		*word;


	t = 1;
	while (t)
	{
		cmd = readline("Prompt > ");
		add_history(cmd);

		cmd_list = ft_split(cmd, ' ');
		i = 0;
		word = NULL;
		while (cmd_list[i] != NULL)
		{
			word = struct_init(cmd_list[i], word, i);
			i++;
		}

		printf("You said : %s\n", cmd);

		//Le code qui suis imprime dans le terminal divers élément afin de tester ce que réalise le reste du programme
		i = 0;
		while (cmd_list[i] != NULL)
		{
			if (find_word(word, i)->is_token == 1)
				printf("Token : %s\n", find_word(word, i)->word);
			else
				printf("Word : %s\n", find_word(word, i)->word);
			i++;
		}
	}
	return (0);
}