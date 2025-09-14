/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:40:33 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/14 16:59:06 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_cmd *cmd, int in_fd, int out_fd, t_env **env)
{
	char	**envp;
	char	*path;

	if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != 1)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	path = find_in_path(cmd->argv[0], *env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		_exit(127);
	}
	envp = env_to_envp(*env);
	execve(path, cmd->argv, envp);
	perror("execve");
	free_argv(envp);
	free(path);
	_exit(126);
}

int	execute_pipeline(t_cmd *cmds, t_env **env)
{
	t_cmd	*cur;
	int		pipe_fd[2];
	int		in_fd;
	pid_t	pid;

	cur = cmds;
	in_fd = 0;
	while (cur)
	{
		if (cur->next)
		{
			if (pipe(pipe_fd) < 0)
			{
				perror("pipe");
				return (1);
			}
		}
		else
		{
			pipe_fd[1] = 1;
			pipe_fd[0] = 0;
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return (1);
		}
		else if (pid == 0)
		{
			if (cur->next)
				close(pipe_fd[0]); // child doesn't read from pipe
			child_process(cur, in_fd, pipe_fd[1], env);
		}
		if (in_fd != 0)
			close(in_fd); // close if not stdin
		if (cur->next)
		{
			close(pipe_fd[1]);
			in_fd = pipe_fd[0]; // next process reads from here
		}
		cur = cur->next;
	}
	while (wait(NULL) > 0)
		; // wait for all children
	return (0);
}
