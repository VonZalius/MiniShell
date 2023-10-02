/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:53:38 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/02 14:26:10 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen_space(const char *s, size_t i)
{
	while (s[i] != ' ' && s[i] != '\0' && s[i] != '|'
		&& s[i] != '<' && s[i] != '>' && s[i] != '$')
		i++;
	return (i);
}

char	*s_f_e_bis(char *cmd, t_lexer *word)
{
	int		i;
	int		j;
	char	*str2;

	i = 0;
	if (cmd[word->i] == '$')
	{
		if (cmd[word->i + 1] == ' ' || cmd[word->i + 1] == '\0')
			return (cmd);
		word->i++;
		j = word->i;
		str2 = malloc(sizeof(char) * (ft_strlen_space(cmd, word->i) + 1));
		while (cmd[j] != '\0' && cmd[j] != ' ' && cmd[j] != '"'
			&& cmd[j] != '|' && cmd[j] != '<' && cmd[j] != '>' && cmd[j] != '$')
		{
			str2[i] = cmd[j];
			i++;
			j++;
		}
		str2[i] = '\0';
		cmd = ft_strinsert(cmd, getenv(str2), word->i - 1);
		if (cmd == NULL)
			return (NULL);
		//free(str2);
	}
	return (cmd);
}

int	s_f_e_skip(t_lexer *word, char *cmd)
{
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

char	*search_for_env(t_lexer *word, char *cmd, int start)
{
	int		check;

	//printf("-> search_for_env...\n");
	word->i = start;
	check = 0;
	while (cmd[word->i] != '\0')
	{
		if (cmd[word->i] == '\"' && check == 0)
			check = 1;
		else if (cmd[word->i] == '\"' && check == 1)
			check = 0;
		if (cmd[word->i] == '|' && check == 0)
			return (cmd);
		if (s_f_e_skip(word, cmd) == 0)
			return (NULL);
		if (cmd[word->i] == '$' && cmd[word->i + 1] == '?')
			cmd = dollar_search(cmd, word);
		else
			cmd = s_f_e_bis(cmd, word);
		if (cmd == NULL)
			return (NULL);
		word->i++;
	}
	return (cmd);
}
