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

void	child_process(t_cmd *cmd, int in_fd, int out_fd, t_env **env)
{
	setup_io_fds(in_fd, out_fd);
	handle_redirections(cmd);
	if (!cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		_exit(0);
	exec_child_builtin_or_execve(cmd, env);
}
