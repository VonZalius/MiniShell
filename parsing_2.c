#include "minishell.h"

int	how_many_arg(char *cmd, int i_bis, int j)
{
	while (cmd[i_bis] != '\0' && cmd[i_bis] != '|')
	{
		if (cmd[i_bis] == ' ')
		{
			//printf("X - - - - - >  Space detected [%c]\n", cmd[i_bis]);
			while (cmd[i_bis] == ' ')
				i_bis++;
		}
		else if (cmd[i_bis] == '<' || cmd[i_bis] == '>')
		{
			//printf("X - - - - - >  '<' or '>' detected [%c]\n", cmd[i_bis]);
			i_bis++;
			while(cmd[i_bis] != ' ' && cmd[i_bis] != '\0' && cmd[i_bis] != '|' && cmd[i_bis] != '<' && cmd[i_bis] != '>')
				i_bis++;
		}

		else
		{
			//printf("X - - - - - >  Word or Argumet detected [%c]\n", cmd[i_bis]);
			while(cmd[i_bis] != ' ' && cmd[i_bis] != '\0' && cmd[i_bis] != '|' && cmd[i_bis] != '<' && cmd[i_bis] != '>')
			{
				if(cmd[i_bis] == '\'')
				{
					i_bis++;
					while(cmd[i_bis] != '\'')
						i_bis++;
				}
				if(cmd[i_bis] == '\"')
				{
					i_bis++;
					while(cmd[i_bis] != '\"')
						i_bis++;
				}
				i_bis++;
			}
			j++;
		}
	}
	//printf("X - - - - - > Total nbr of arg detected = [%i]\n", j - 1);
	/*while (cmd[i_bis] != '\0' && cmd[i_bis] != '|')
	{
		if (i_bis == copy && cmd[i_bis] == ' ')
		{
			while (cmd[i_bis] == ' ')
				i_bis++;
		}
		else if (cmd[i_bis] == '\"')
		{
			i_bis++;
			while (cmd[i_bis] != '\"' && cmd[i_bis] != '\0')
				i_bis++;
			i_bis++;
		}
		else if (cmd[i_bis] == '\'')
		{
			i_bis++;
			while (cmd[i_bis] != '\'' && cmd[i_bis] != '\0')
				i_bis++;
			i_bis++;
		}
		else if (cmd[i_bis] == '<' || cmd[i_bis] == '>')
		{
			while (cmd[i_bis] == '<' || cmd[i_bis] == '>')
				i_bis++;
			j--;
		}
		else if (cmd[i_bis] == ' ')
		{
			while (cmd[i_bis] == ' ')
				i_bis++;
			if (cmd[i_bis] == '|' || cmd[i_bis] == '\0')
				return (j);
			if (cmd[i_bis] == '<' || cmd[i_bis] == '>')
			{
				while (cmd[i_bis] == '<' || cmd[i_bis] == '>')
					i_bis++;
				j--;
			}
			j++;
		}
		else
			i_bis++;

	}*/
	return (j - 1);
}