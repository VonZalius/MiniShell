/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:53:38 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/02 14:26:04 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_search(char *cmd, t_lexer *word)
{
	cmd = ft_strinsert(cmd, ft_itoa(word->dol), word->i);
	return (cmd);
}

int	ft_len_of_dol(char *str1)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	while (str1[i] != '\0')
	{
		if (str1[i] == '$' && str1[i + 1] == '?')
			return (1);
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

int	ft_strinsert_last(t_mini *mini, char *str1, char *str2)
{
	mini->j++;
	if (str2 == NULL)
		return (0);
	while (str2 != NULL && str2[mini->k] != '\0')
	{
		mini->final[mini->i] = str2[mini->k];
		mini->k++;
		mini->i++;
	}
	if (str1[mini->j - 1] == '$' && str1[mini->j] == '?')
	{
		mini->j++;
	}
	else
		while (str1[mini->j] != ' ' && str1[mini->j] != '\0'
			&& str1[mini->j] != '"' && str1[mini->j] != '|'
			&& str1[mini->j] != '<' && str1[mini->j] != '>'
			&& str1[mini->j] != '$')
			mini->j++;
	return (1);
}

int	ft_strinsert_bis(t_mini *mini, char *str1, char *str2, int pos)
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
			if (ft_strinsert_last(mini, str1, str2) == 0)
				return (0);
		}
	}
	return (0);
}

char	*ft_strinsert(char *str1, char *str2, int pos)
{
	t_mini	mini;

	mini.len = ft_strlen(str1) + ft_strlen(str2) - ft_len_of_dol(str1);
	mini.final = malloc (sizeof(char) * (mini.len) + 1);
	if (mini.final == NULL)
		return (NULL);
	mini.i = 0;
	mini.j = 0;
	mini.k = 0;
	ft_strinsert_bis(&mini, str1, str2, pos);
	mini.final[mini.i] = '\0';
	return (mini.final);
}
