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

void	child_process(t_cmd *cmd, int in_fd, int out_fd, t_env **env)
{
	char	**envp;
	char	*path;
	int		exit_code;

	if (!cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		_exit(0);
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
	if (cmd->redir)
	{
		if (apply_redirections(cmd) != 0)
			_exit(1);
	}
	if (is_builtin(cmd->argv[0]))
		_exit(run_builtin(cmd->argv, env));
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
	{
		path = find_in_path(cmd->argv[0], *env);
	}
	if (!path)
		_exit(127);

	exit_code = check_exec_path(path);
	if (exit_code != 0)
	{
		free(path);
		_exit(last_status(1, exit_code));
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
