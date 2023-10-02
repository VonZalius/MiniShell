/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:20:33 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/02 15:42:28 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//MODIFIER PRINTF

#include "../minishell.h"

void	malloc_error(char **error)
{
	printf("Memory allocation failed\n");
	free (error);
	exit(1);
}

void	malloc_error_1(char *error)
{
	printf("Memory allocation failed\n");
	free (error);
	exit(1);
}
