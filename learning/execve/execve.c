/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:33:56 by root              #+#    #+#             */
/*   Updated: 2025/08/16 17:34:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	char *args[] = {"/bin/ls", "-l", NULL};
	char *envp[] = {
		"PATH=/usr/bin:/bin",
		"LANG=C",
		NULL
	};

	execve(args[0], args, envp);
	perror("execve");
	return (1);
}
