/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:38:18 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/24 15:38:20 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command(char **argv, t_shell *sh)
{
	size_t	i;

	(void)sh;
	if (!argv || !argv[0])
		return (0);
	printf("[exec stub] tokens:");
	i = 0;
	while (argv[i])
		printf(" {%s}", argv[i++]);
	printf("\n");
	return (0);
}
