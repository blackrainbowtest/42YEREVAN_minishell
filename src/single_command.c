/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 00:28:10 by aramarak          #+#    #+#             */
/*   Updated: 2025/11/04 00:40:54 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_last_arg(t_cmd *cmd, t_env **env)
{
	int	last;

	last = 0;
	if (!cmd->argv || !cmd->argv[0])
		return ;
	while (cmd->argv[last + 1])
		last++;
	ft_setenv(env, "_", cmd->argv[last], 1);
}

// void	run_single_command(t_cmd *cmd, t_env **env)
// {
// 	pid_t	pid;
// 	int		exit_code;
// 	int		i;

// 	if (!cmd)
// 		return ;
// 	if (prepare_heredocs(cmd) < 0)
// 		return ;
// 	if (!cmd->argv)
// 		return ;
// 	i = 0;
// 	while (cmd->argv[i] && cmd->argv[i][0] == '\0')
// 		i++;
// 	if (!cmd->argv[i])
// 		return ;
// 	if (is_direct_builtin(cmd->argv[i]))
// 	{
// 		run_builtin(&cmd->argv[i], env);
// 		return ;
// 	}
// 	update_last_arg(cmd, env);
// 	in_child_process(1, 1);
// 	pid = fork();
// 	if (pid < 0)
// 		return ((void)perror("fork"));
// 	if (pid == 0)
// 		exec_child_process(cmd, env, i);
// 	exit_code = wait_for_child(pid);
// 	in_child_process(1, 0);
// 	last_status(1, exit_code);
// }

static int	skip_empty_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i] && cmd->argv[i][0] == '\0')
		i++;
	if (!cmd->argv[i])
		return (-1);
	return (i);
}

static int	handle_direct_builtin(t_cmd *cmd, t_env **env, int i)
{
	int	exit_code;

	if (is_direct_builtin(cmd->argv[i]))
	{
		exit_code = run_builtin(&cmd->argv[i], env);
		last_status(1, exit_code);
		return (1);
	}
	return (0);
}

static int	spawn_child_process(t_cmd *cmd, t_env **env, int i)
{
	pid_t	pid;
	int		exit_code;

	update_last_arg(cmd, env);
	in_child_process(1, 1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		exec_child_process(cmd, env, i);
	exit_code = wait_for_child(pid);
	in_child_process(1, 0);
	last_status(1, exit_code);
	return (exit_code);
}

void	run_single_command(t_cmd *cmd, t_env **env)
{
	int	i;

	if (!cmd)
		return ;
	if (prepare_heredocs(cmd) < 0)
		return ;
	if (!cmd->argv)
		return ;
	i = skip_empty_args(cmd);
	if (i < 0)
		return ;
	if (handle_direct_builtin(cmd, env, i))
		return ;
	spawn_child_process(cmd, env, i);
}
