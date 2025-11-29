/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:33:49 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/16 19:46:31 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_minishell_error(char *cmd, char *arg, char *msg, int status)
{
	char	buf[1024];
	int		len;

	if (!cmd)
		cmd = "";
	if (!arg)
		arg = "";
	if (!msg)
		msg = "";
	if (arg[0])
		len = snprintf(buf, sizeof(buf),
				"minishell: %s: %s: %s\n", cmd, arg, msg);
	else
		len = snprintf(buf, sizeof(buf),
				"minishell: %s: %s\n", cmd, msg);

	write(2, buf, len);
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

int	in_child_process(int mode, int value)
{
	static int	in_child;

	if (mode == 1)
		in_child = value;
	return (in_child);
}
