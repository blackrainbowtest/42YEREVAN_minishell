/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:39:30 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/17 16:40:07 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/**
 * @brief Demonstrates handling of signals in a process.
 * This program sets up a signal handler for SIGINT (Ctrl+C).
 * When the signal is received, it prints a message and continues running.
 * 
 * @return Returns 0 on successful execution.
 */
void	handle_sigint(int sig)
{
	printf("\nCaught signal %d (SIGINT)\n", sig);
}

int	main(void)
{
	signal(SIGINT, handle_sigint);
	printf("PID=%d, try Ctrl+C\n", getpid());
	while (1)
		sleep(1);
	return (0);
}
