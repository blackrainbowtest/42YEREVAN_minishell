/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:38:18 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/02 22:00:14 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	spawn_and_wait(char *path, char **argv, t_shell *sh)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		execve(path, argv, sh->env);
		perror("execve");
		_exit (126);
	}
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		return (1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	execute_command(char **argv, t_shell *sh)
{
	char	*path;
	int		code;

	if (!argv || !argv[0])
		return (0);
	if (strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	path = find_in_path(argv[0], sh->env);
	if (!path)
	{
		fprintf(stderr, "minishell: %s: command not found\n", argv[0]);
		return (127);
	}
	code = spawn_and_wait(path, argv, sh);
	free(path);
	return (code);
}
