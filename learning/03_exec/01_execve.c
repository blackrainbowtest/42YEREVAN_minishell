/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:51:14 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/17 16:52:55 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

/**
 * @brief Demonstrates the use of execve to execute a program.
 * This program attempts to execute the `ls` command with the `-l` option.
 * If successful, it will not return to this code.
 * If it fails, it will print an error message.
 * 
 * @return Returns 1 on failure, as execve does not return on success.
 */
int	main(void)
{
	char	*args[3];
	char	*env[1];

	args[0] = "/bin/ls";
	args[1] = "-l";
	args[2] = NULL;
	env[0] = NULL;
	execve(args[0], args, env);
	perror("execve failed");
	return (1);
}
