/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex03_zombie.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:17:40 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/17 16:18:41 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/**
 * @brief Demonstrates a zombie process.
 * This program forks a child process that exits immediately,
 * while the parent process sleeps for 10 seconds, allowing
 * the child to become a zombie.
 * 
 * @return Returns 0 on successful execution.
 */
int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		printf("Child exiting, PID = %d\n", getpid());
		exit(0);
	}
	else if (pid > 0)
	{
		printf("Parent PID = %d, sleeping 10s...\n", getpid());
		sleep(10);
	}
	return (0);
}
