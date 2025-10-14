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
	/* В дочернем heredoc: SIGINT — дефолт (чтобы завершиться), SIGQUIT — игнор */
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

/* --- Loop чтения heredoc — выполняется в дочернем процессе --- */
static void	heredoc_loop(int write_fd, const char *limiter)
{
	char	*line;

	heredoc_child_signals();
	/* Читаем построчно до лимитера. readline возвращает NULL на EOF (Ctrl+D). */
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			/* EOF (Ctrl+D) — просто завершаем ввод */
			/* Bash выводит предупреждение в некоторых случаях, но это опционально */
			exit(0);
		}
		/* Сравнение: точная строка (без '\n') */
		if (strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		/* Здесь можно вставить расширение переменных, если нужно:
		   - если limiter не был в кавычках -> выполнить expand_line(line, env)
		   - else оставить как есть.
		   expand_line должна возвращать malloc'd строку.
		*/
		write(write_fd, line, strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
	exit(0);
}

/* --- Ожидание дочернего процесса и возврат результата --- */
static int	wait_heredoc_child(pid_t pid, int pipefd[2])
{
	int	status;

	/* В родителе мы закрываем write-энд и ждём ребёнка */
	close(pipefd[1]);
	if (waitpid(pid, &status, 0) == -1)
	{
		close(pipefd[0]);
		return (-1);
	}
	/* Если child был прерван сигналом (например Ctrl+C) — считаем ошибкой */
	if (WIFSIGNALED(status))
	{
		/* закрываем read end, caller получит -1 */
		close(pipefd[0]);
		return (-1);
	}
	/* Если ребёнок завершился с ненулевым кодом — тоже считаем ошибкой */
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(pipefd[0]);
		return (-1);
	}
	/* Всё ок — возвращаем read end */
	return (pipefd[0]);
}

/* -------------------- Публичная функция --------------------
   Использование: fd = open_heredoc("EOF");
   При успехе возвращает fd (read-end). При ошибке или прерывании — -1.
*/
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
		/* child */
		close(pipefd[0]); /* закрываем read в child */
		heredoc_loop(pipefd[1], limiter);
		/* heredoc_loop не вернётся */
	}
	/* parent */
	ret = wait_heredoc_child(pid, pipefd);
	return (ret);
}
