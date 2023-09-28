/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:53:38 by cmansey           #+#    #+#             */
/*   Updated: 2023/09/28 12:57:23 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len_of_dol(char *str1)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	while (str1[i] != '\0')
	{
		if (str1[i] == '$')
		{
			i++;
			while (str1[i] != ' ' && str1[i] != '\0' && str1[i] != '"'
				&& str1[i] != '|' && str1[i] != '<'
				&& str1[i] != '>' && str1[i] != '$')
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

void	ft_strinsert_bis(t_mini *mini, char *str1, char *str2, int pos)
{
	while (mini->i != mini->len)
	{
		if (mini->i != pos)
		{
			mini->final[mini->i] = str1[mini->j];
			mini->j++;
			mini->i++;
		}
		else
		{
			mini->j++;
			while (str2[mini->k] != '\0')
			{
				mini->final[mini->i] = str2[mini->k];
				mini->k++;
				mini->i++;
			}
			while (str1[mini->j] != ' ' && str1[mini->j] != '\0'
				&& str1[mini->j] != '"' && str1[mini->j] != '|'
				&& str1[mini->j] != '<' && str1[mini->j] != '>'
				&& str1[mini->j] != '$')
				mini->j++;
		}
	}
}

char	*ft_strinsert(char *str1, char *str2, int pos)
{
	t_mini	mini;

	if (str2 == NULL)
		return (NULL);
	mini.len = ft_strlen(str1) + ft_strlen(str2) - ft_len_of_dol(str1);
	mini.final = malloc (sizeof(char) * (mini.len) + 1);
	if (mini.final == NULL)
		return (NULL);
	mini.i = 0;
	mini.j = 0;
	mini.k = 0;
	ft_strinsert_bis(&mini, str1, str2, pos);
	free (str1);
	mini.final[mini.i] = '\0';
	return (mini.final);
}

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
	}
	return (cmd);
}

char	*dollar()
{
	char	*buffer;
	int		bytes_read;
	int		fd;

	fd = open("pipe_handler", 0);
	if (fd < 0)
		return (NULL);
	buffer = malloc(sizeof(char) * 1024);
	bytes_read = read(fd, buffer, 1024);
	buffer[bytes_read] = '\0';
	close(fd);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char	*search_for_env(t_lexer *word, char *cmd, int start)
{
	char	*ddollar;
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
		{
			ddollar = dollar();
			if (ddollar == NULL)
				return (NULL);
			cmd = ft_strinsert(cmd, ddollar, word->i);
			free (ddollar);
		}
		else
			cmd = s_f_e_bis(cmd, word);
		if (cmd == NULL)
			return (NULL);
		word->i++;
	}
	return (cmd);
}
