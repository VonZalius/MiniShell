/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:19:51 by abarras           #+#    #+#             */
/*   Updated: 2023/09/28 15:02:19 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

char	*ft_strdup(const char *src)
{
	int		i;
	int		j;
	char	*back;

	i = 0;
	back = NULL;
	while (src[i] != '\0')
		i++;
	j = 0;
	back = malloc((i + 1) * sizeof(char));
	if (!back)
		return (back);
	while (src[j] != '\0')
	{
		back[j] = src[j];
		j++;
	}
	back[j] = '\0';
	return (back);
}
/*
int main()
{
	char str[] = "hello c'est moi je suis sympa";
	printf("%s", ft_strdup(str));
}*/
