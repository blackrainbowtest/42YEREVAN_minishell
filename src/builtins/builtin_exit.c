/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:39:32 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/12 01:22:51 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(char **argv)
{
	int	status;

	ft_putendl_fd("exit", 1);
	if (!argv[1])
		exit(0);
	status = ft_atoi(argv[1]);
	exit(status);
}
