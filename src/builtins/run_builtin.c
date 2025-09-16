/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 19:54:39 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/07 22:39:03 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (strcmp(cmd, "echo") == 0
		|| strcmp(cmd, "cd") == 0
		|| strcmp(cmd, "pwd") == 0
		|| strcmp(cmd, "env") == 0
		|| strcmp(cmd, "export") == 0
		|| strcmp(cmd, "unset") == 0
		|| strcmp(cmd, "exit") == 0);
}

int	is_parent_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (strcmp(cmd, "cd") == 0
		|| strcmp(cmd, "export") == 0
		|| strcmp(cmd, "unset") == 0
		|| strcmp(cmd, "exit") == 0);
}

int	run_builtin(char **argv, t_env **env)
{
	if (!argv || !argv[0])
		return (EXIT_SUCCESS);
	if (strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argv));
	if (strcmp(argv[0], "cd") == 0)
		return (builtin_cd(argv, env));
	if (strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd(*env));
	if (strcmp(argv[0], "env") == 0)
		return (builtin_env(*env));
	if (strcmp(argv[0], "export") == 0)
		return (builtin_export(argv, env));
	if (strcmp(argv[0], "unset") == 0)
		return (builtin_unset(argv, env));
	if (strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argv));
	return (EXIT_SUCCESS);
}
