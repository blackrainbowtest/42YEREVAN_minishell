/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:40:33 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/14 14:16:04 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
