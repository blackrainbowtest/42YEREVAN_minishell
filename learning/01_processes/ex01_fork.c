/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex01_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:09:31 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/17 16:11:21 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		printf("Child process, PID = %d\n", getpid());
	else if (pid > 0)
		printf("Parent process, PID = %d, Child PID = %d\n", getpid(), pid);
	else
		perror("fork failed");
	return (0);
}
