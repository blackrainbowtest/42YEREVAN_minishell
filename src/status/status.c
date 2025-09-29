/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:33:49 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/29 22:36:10 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_minishell_error(char *cmd, char *arg,
	char *msg, int status)
{
	if (cmd && *cmd)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg && *arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg && *msg)
		ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	last_status(1, status);
	return (status);
}

int	last_status(int mode, int new_value)
{
	static int	status;

	if (mode == 1)
		status = new_value;
	return (status);
}
