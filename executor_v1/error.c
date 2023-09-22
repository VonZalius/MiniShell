/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:20:33 by cmansey           #+#    #+#             */
/*   Updated: 2023/08/07 19:21:29 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//MODIFIER PRINTF

#include "mini_shell.h"

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
