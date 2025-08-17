/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_fork_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:53:32 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/17 16:54:44 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(void)
{
	pid_t	pid;
	int		status;
	char	*args[3];
	char	*env[1];

	pid = fork();
	if (pid == 0)
	{
		args[0] = "/bin/ls";
		args[1] = "-l";
		args[2] = NULL;
		env[0] = NULL;
		execve(args[0], args, env);
		perror("execve failed");
		_exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			printf("Child exited with %d\n", WEXITSTATUS(status));
	}
	return (0);
}
