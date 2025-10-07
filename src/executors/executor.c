/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:38:18 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/06 01:40:53 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_child(char *path, char **argv, char **envp)
{
	pid_t	pid;
	int		exit_code;

	in_child_process(1, 1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		signal_default();
		if (path == NULL || path[0] == '\0')
			_exit(126);
		if (access(path, F_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(argv[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			_exit(last_status(1, 127));
		}
		exit_code = check_exec_path(path);
		if (exit_code != 0)
			_exit(last_status(1, exit_code));
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
		last_status(1, 1);
		return (1);
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

	i = 0;
	if (!argv)
		return (0);
	while (argv[i] && argv[i][0] == '\0')
		i++;
	if (!argv[0])
		return (0);
	cmd = argv[i];
	if (ft_strchr(cmd, '/'))
		path = ft_strdup(cmd);
	else
		path = find_in_path(cmd, env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (last_status(1, 127));
	}

	exit_code = check_exec_path(path);
	if (exit_code != 0)
	{
		free(path);
		return (last_status(1, exit_code));
	}
	printf("[DEBUG EXEC] path='%s'\n", path);
	for (int j = 0; argv[j]; j++)
		printf("argv[%d]='%s'\n", j, argv[j]);
	exit_code = spawn_and_wait(path, argv, env);
	free(path);
	return (exit_code);
}
