/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:39:32 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/28 00:35:26 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoll(const char *str)
{
	long long	res;
	int			sign;
	int			i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

int	is_numeric_arg(char *arg)
{
	int	i;

	if (!arg || !*arg)
		return (0);
	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	get_exit_status(const char *str)
{
	return ((unsigned char)ft_atoll(str));
}

int	builtin_exit(char **argv)
{
	if (!argv[1])
		exit(0);
	if (!is_numeric_arg(argv[1]))
		exit(print_minishell_error("exit", argv[1], ERR_NUMERIC, 2));
	if (argv[2])
		return (print_minishell_error("exit", NULL, ERR_TOO_MNY_ARGS, 1));
	exit(last_status(1, get_exit_status(argv[1])));
}
