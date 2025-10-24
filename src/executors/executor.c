/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:38:18 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/24 00:49:23 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_child(char *path, char **argv, char **envp)
{
	int	exit_code;

	signal_default();
	if (!path || !path[0])
		_exit(126);
	if (access(path, F_OK) != 0)
		_exit(print_minishell_error(argv[0], NULL, ERR_DIR, 127));
	exit_code = check_exec_path(path);
	if (exit_code != 0)
		_exit(last_status(1, exit_code));
	execve(path, argv, envp);
	perror("execve");
	_exit(126);
}

static int	execute_child(char *path, char **argv, char **envp)
{
	pid_t	pid;

	in_child_process(1, 1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		run_child(path, argv, envp);
	return (pid);
}

static int	spawn_and_wait(char *path, char **argv, t_env *env)
{
	pid_t	pid;
	int		status;
	char	**envp;
	int		exit_code;

	envp = env_to_envp(env);
	if (!envp)
		return (1);
	pid = execute_child(path, argv, envp);
	free_argv(envp);
	in_child_process(1, 0);
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		return (last_status(1, 1));
	}
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	else
		exit_code = 1;
	last_status(1, exit_code);
	return (exit_code);
}

int	execute_command(char **argv, t_env *env)
{
	char	*path;
	char	*cmd;
	int		i;
	int		exit_code;

	if (!argv)
		return (0);
	i = 0;
	while (argv[i] && argv[i][0] == '\0')
		i++;
	if (!argv[i])
		return (0);
	cmd = argv[i];
	if (ft_strchr(cmd, '/'))
		path = ft_strdup(cmd);
	else
		path = find_in_path(cmd, env);
	if (!path)
		return (print_minishell_error(cmd, NULL, "command not found", 127));
	exit_code = check_exec_path(path);
	if (exit_code != 0)
		return (free(path), last_status(1, exit_code));
	exit_code = spawn_and_wait(path, argv, env);
	free(path);
	return (exit_code);
}
