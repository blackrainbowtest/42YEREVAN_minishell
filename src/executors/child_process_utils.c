/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 23:54:41 by aramarak          #+#    #+#             */
/*   Updated: 2025/11/04 00:12:39 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*resolve_command_path(t_cmd *cmd, t_env *env)
{
	char	*path;

	path = NULL;
	if (ft_strchr(cmd->argv[0], '/'))
	{
		path = ft_strdup(cmd->argv[0]);
		if (access(path, F_OK) != 0)
		{
			perror("path");
			_exit(127);
		}
	}
	else
		path = find_in_path(cmd->argv[0], env);
	if (!path)
	{
		print_minishell_error(cmd->argv[0], NULL, "command not found", 127);
		_exit(127);
	}
	return (path);
}

static void	update_last_argument(t_cmd *cmd, t_env **env)
{
	int	last;

	last = 0;
	if (!cmd->argv || !cmd->argv[0])
		return ;
	while (cmd->argv[last + 1])
		last++;
	ft_setenv(env, "_", cmd->argv[last], 1);
}

void	exec_child_builtin_or_execve(t_cmd *cmd, t_env **env)
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
	update_last_argument(cmd, env);
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
