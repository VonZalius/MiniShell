/*#include "minishell.h"

int ft_len_of_t(char *str1)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	while (str1[i] != '\0')
	{
		if(str1[i] == '<')
		{
			while(str1[i] == '<')
            {
                i++;
                b++;
            }
            while(str1[i] == ' ')
            {
                b++;
                i++;
            }
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

#include "minishell.h"

void	ft_strinsert_bi(mini *mini, char *str1, char *str2, int pos)
{
	while(mini->i != mini->len)
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

char *rev_strcat(char *dest, char src)
{
	int i;
	int j;
    char save;

	j = 0;
    i = ft_strlen(dest) + 1;

	while (j != i)
	{
		save = dest[j];
        dest[j] = src;
        src = save;
        j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*ft_strinsert_fd(char *str1, char *str2, int pos)
{
	mini mini;

	if (str2 == NULL)
		return (NULL);
    str2 = rev_strcat(str2, '\"');
    str2 = ft_strcat(str2, "\"");
	mini.len = ft_strlen(str1) + ft_strlen(str2) - ft_len_of_t(str1);
	mini.final = malloc (sizeof(char) * (mini.len) + 1);
	if (mini.final == NULL)
		return (NULL);
	mini.final[mini.len] = '\0';
	mini.i = 0;
	mini.j = 0;
	mini.k = 0;
	ft_strinsert_bi(&mini, str1, str2, pos);
	free (str1);
    mini.final[mini.len] = '\0';
	return (mini.final);
boum
}*/
