/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:40:33 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/25 02:08:03 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_for_children(pid_t last_pid)
{
	int		status;
	int		exit_code;
	pid_t	finished;
	int		sig;

	exit_code = 0;
	while ((finished = wait(&status)) > 0)
	{
		if (finished == last_pid)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (sig == SIGPIPE)
					exit_code = 0;
				else
					exit_code = 128 + sig;
			}
		}
	}
	return (exit_code);
}

static int	fork_and_run(t_cmd *cur, int in_fd, int *pipe_fd, t_env **env)
{
	pid_t	pid;
	int		out_fd;

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
		if (cur->next)
			close(pipe_fd[0]);
		out_fd = STDOUT_FILENO;
		if (cur->next)
			out_fd = pipe_fd[1];
		child_process(cur, in_fd, out_fd, env);
		_exit(42);
	}
	return (pid);
}

static int	setup_pipe(t_cmd *cur, int pipe_fd[2])
{
	if (cur->next && pipe(pipe_fd) < 0)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

static void	close_fds(int *in_fd, int *pipe_fd, t_cmd *cur)
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (cur->next)
	{
		close(pipe_fd[1]);
		*in_fd = pipe_fd[0];
	}
}

int	execute_pipeline(t_cmd *cmds, t_env **env)
{
	t_cmd	*cur;
	int		pipe_fd[2];
	int		in_fd;
	pid_t	last_pid;
	int		exit_code;

	cur = cmds;
	in_fd = STDIN_FILENO;
	last_pid = -1;
	if (prepare_heredocs(cmds) < 0)
		return (1);
	while (cur)
	{
		if (setup_pipe(cur, pipe_fd) < 0)
			return (1);
		last_pid = fork_and_run(cur, in_fd, pipe_fd, env);
		if (last_pid < 0)
			return (1);
		close_fds(&in_fd, pipe_fd, cur);
		cur = cur->next;
	}
	exit_code = wait_for_children(last_pid);
	in_child_process(1, 0);
	return (last_status(1, exit_code));
}
