/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:38:18 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/11 19:53:05 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_child(char *path, char **argv, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		execve(path, argv, envp);
		perror("execve");
		_exit(126);
	}
	return (pid);
}

static int	spawn_and_wait(char *path, char **argv, t_env *env)
{
	pid_t	pid;
	int		status;
	char	**envp;

	envp = env_to_envp(env);
	if (!env)
		return (1);
	pid = execute_child(path, argv, envp);
	free_argv(envp);
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

int	execute_command(char **argv, t_env *env)
{
	char	*path;
	int		code;

	if (!argv || !argv[0])
		return (0);
	path = find_in_path(argv[0], env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	code = spawn_and_wait(path, argv, env);
	free(path);
	return (code);
}
