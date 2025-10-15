/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:40:33 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/14 16:59:06 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_trunc(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror(file);
	return (fd);
}

int	open_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		perror(file);
	return (fd);
}

int	open_read(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		perror(file);
	return (fd);
}

static void	heredoc_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

static void	heredoc_loop(int write_fd, const char *limiter)
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

static int	wait_heredoc_child(pid_t pid, int pipefd[2])
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

int	open_heredoc(char *limiter)
{
	int		pipefd[2];
	pid_t	pid;
	int		ret;

	if (!limiter)
		return (-1);
	if (pipe(pipefd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		heredoc_loop(pipefd[1], limiter);
	}
	ret = wait_heredoc_child(pid, pipefd);
	return (ret);
}
