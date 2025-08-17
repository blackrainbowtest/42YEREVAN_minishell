/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_waitpid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:35:58 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/17 16:37:02 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(void)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	pid1 = fork();
	pid2 = fork();
	if (pid1 == 0 || pid2 == 0)
	{
		printf("Child PID=%d exiting\n", getpid());
		exit(1);
	}
	else
	{
		printf("Parent waiting for specific child PID=%d\n", pid1);
		waitpid(pid1, &status, 0);
		if (WIFEXITED(status))
			printf("Child PID=%d exited with %d\n", pid1, WEXITSTATUS(status));
	}
	return (0);
}
