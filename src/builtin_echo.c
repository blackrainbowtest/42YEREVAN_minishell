/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:38:56 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/03 19:38:56 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Implementation of the "echo" builtin command.
 *
 * Prints its arguments to the standard output. If the first argument
 * is "-n", the trailing newline is suppressed. Multiple arguments
 * are separated by a single space.
 *
 * @param args A NULL-terminated array of strings.
 *             - args[0]: the command name ("echo")
 *             - args[1..n]: the arguments to be printed
 *
 * @return Always returns 0.
 *
 * @note This function writes directly to stdout using printf() and write().
 */
int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[1] && strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
