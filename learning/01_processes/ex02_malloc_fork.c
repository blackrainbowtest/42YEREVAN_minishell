/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex02_malloc_fork.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:12:31 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/17 16:14:08 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int	main(void)
{
	int		*num;
	pid_t	pid;

	num = malloc(sizeof(int));
	*num = 42;
	pid = fork();
	if (pid == 0)
	{
		printf("Child sees num = %d\n", *num);
		*num = 100;
		free(num);
	}
	else if (pid > 0)
	{
		printf("Parent sees num = %d\n", *num);
		free(num);
	}
	return (0);
}
