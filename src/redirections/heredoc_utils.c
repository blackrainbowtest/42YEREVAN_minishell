/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:33:11 by aramarak          #+#    #+#             */
/*   Updated: 2025/11/08 11:09:17 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_loop(int write_fd, const char *limiter)
{
	char	*line;

	heredoc_child_signals();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			exit(0);
		}
		if (strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
	exit(0);
}

int	wait_heredoc_child(pid_t pid, int pipefd[2])
{
	int	status;

	close(pipefd[1]);
	if (waitpid(pid, &status, 0) == -1)
	{
		close(pipefd[0]);
		return (-1);
	}
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			last_status(1, 130);
		}
		close(pipefd[0]);
		return (-1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(pipefd[0]);
		return (-1);
	}
	return (pipefd[0]);
}
