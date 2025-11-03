/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 19:54:39 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/07 22:39:03 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unset_single(char *arg, t_env **env)
{
	if (ft_strcmp(arg, "_") == 0)
		return (0);
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	if (ft_unsetenv(env, arg) != 0)
		return (1);
	return (0);
}

int	builtin_unset(char **argv, t_env **env)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	while (argv[i])
	{
		if (unset_single(argv[i], env))
			status = 1;
		i++;
	}
	return (status);
}
