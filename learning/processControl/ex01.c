/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex01.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:40:03 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/17 15:40:43 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * @brief Demonstrates process creation and waiting for a child process.
 * This program forks a child process, which sleeps for 2 seconds
 * and then exits with a status code of 42.
 * 
 * The parent process waits for the child to finish and retrieves
 * the exit status of the child process.
 * 
 * @return Returns 0 on successful execution.
 */
int	main(void)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		printf("Child running (pid=%d)\n", getpid());
		sleep(2);
		exit(42);
	}
	else
	{
		printf("Parent waiting for child...\n");
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			printf("Child exited with code %d\n", WEXITSTATUS(status));
	}
	return (0);
}
