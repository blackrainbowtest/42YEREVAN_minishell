/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:38:18 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/26 19:55:39 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command(char **argv, t_shell *sh)
{
	pid_t	pid;
	int		status;

	(void)sh;
	if (!argv || !argv[0])
		return (0);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		execvp(argv[0], argv);
		perror("execvp");
		exit (EXIT_FAILURE);
	}
	else
	{
		if (waitpid(pid, &status, 0) < 0)
		{
			perror("waitpid");
			return (1);
		}
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
		else
			return (1);

	}
}
