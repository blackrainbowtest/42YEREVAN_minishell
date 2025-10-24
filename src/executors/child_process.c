/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:40:33 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/16 19:46:09 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_io_fds(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

static void	handle_redirections(t_cmd *cmd)
{
	if (cmd->redir && apply_redirections(cmd) != 0)
		_exit(1);
}

static char	*resolve_command_path(t_cmd *cmd, t_env *env)
{
	char	*path;

	path = NULL;
	if (ft_strchr(cmd->argv[0], '/'))
	{
		path = ft_strdup(cmd->argv[0]);
		if (access(path, F_OK) != 0)
		{
			perror(path);
			_exit(127);
		}
	}
	else
		path = find_in_path(cmd->argv[0], env);
	if (!path)
		_exit(127);
	return (path);
}

static void	exec_child_builtin_or_execve(t_cmd *cmd, t_env **env)
{
	char	*path;
	char	**envp;
	int		exit_code;

	if (is_builtin(cmd->argv[0]))
		_exit(run_builtin(cmd->argv, env));
	path = resolve_command_path(cmd, *env);
	exit_code = check_exec_path(path);
	if (exit_code != 0)
	{
		free(path);
		_exit(last_status(1, exit_code));
	}
	// TODO: make diff function
	if (cmd->argv && cmd->argv[0])
	{
		int	last = 0;
		while (cmd->argv[last + 1])
			last++;
		ft_setenv(env, "_", cmd->argv[last], 1);
	}
	envp = env_to_envp(*env);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	execve(path, cmd->argv, envp);
	perror("execve");
	free_argv(envp);
	free(path);
	_exit(126);
}

void	child_process(t_cmd *cmd, int in_fd, int out_fd, t_env **env)
{
	setup_io_fds(in_fd, out_fd);
	handle_redirections(cmd);
	if (!cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		_exit(0);
	exec_child_builtin_or_execve(cmd, env);
}

