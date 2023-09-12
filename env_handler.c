#include "minishell.h"

int ft_len_of_$(char *str1)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	while (str1[i] != '\0')
	{
		if(str1[i] == '$')
		{
			i++;
			while(str1[i] != ' ' && str1[i] != '\0' && str1[i] != '"' && str1[i] != '|' && str1[i] != '<' && str1[i] != '>' && str1[i] != '$')
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

char	*ft_strinsert(char *str1, char *str2, int pos)
{
	char	*final;
	int		len;
	int		i;
	int		j;
	int		k;

	if (str2 == NULL)
		return (NULL);
	len = ft_strlen(str1) + ft_strlen(str2) - ft_len_of_$(str1);
	final = malloc (sizeof(char) * (len) + 1);
	if (final == NULL)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while(i != len)
	{
		if (i != pos)
		{
			final[i] = str1[j];
			j++;
			i++;
		}
		else
		{
			j++;
			while (str2[k] != '\0')
			{
				final[i] = str2[k];
				k++;
				i++;
			}
			while (str1[j] != ' ' && str1[j] != '\0' && str1[j] != '"' && str1[j] != '|' && str1[j] != '<' && str1[j] != '>' && str1[j] != '$')
				j++;
		}
	}
	free (str1);
	final[i] = '\0';
	return (final);
}

size_t	ft_strlen_space(const char *s, size_t i)
{
	while (s[i] != ' ' && s[i] != '\0' && s[i] != '|' && s[i] != '<' && s[i] != '>' && s[i] != '$')
		i++;
	return (i);
}

char	*search_for_env(lexer *word, char *cmd, int start)
{
	char	*str2;
	int		i;
	int		j;

	word->i = start;
	while (cmd[word->i] != '\0' && cmd[word->i] != '|')
	{
		i = 0;
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
			word->i = word->i + 2;
		if (cmd[word->i] == '$')
		{
			word->i++;
			j = word->i;
			str2 = malloc(sizeof(char) * (ft_strlen_space(cmd, word->i) + 1));
			while (cmd[j] != '\0' && cmd[j] != ' ' && cmd[j] != '"' && cmd[j] != '|' && cmd[j] != '<' && cmd[j] != '>' && cmd[j] != '$')
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
		word->i++;
	}
	//free (str2);
	return (cmd);
}