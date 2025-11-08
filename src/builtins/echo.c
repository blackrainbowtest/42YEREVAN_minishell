/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:38:56 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/03 19:38:56 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_flag(const char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] == '\0')
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

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
 * @note This function writes directly to stdout using write().
 */
int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[1] && is_n_flag(args[i]))
	{
		newline = 0;
		i = 2;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
