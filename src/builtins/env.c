/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:38:56 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/03 19:38:56 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * TODO: add error when call env <arg>; "env: too many arguments" or 
 * "env: <arg>: No such file or directory"
 */
static int	handle_env_args(char **argv)
{
	if (argv[2])
		return (print_minishell_error("env", NULL, ERR_TOO_MNY_ARGS, 1));
	if (argv[1])
		return (print_minishell_error("env", argv[1],
				"No such file or directory", 127));
	return (0);
}

static void	print_env_vars(t_env *env)
{
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(env->value, 1);
		}
		env = env->next;
	}
}

int	builtin_env(char **argv, t_env *env)
{
	if (argv[1])
		return (handle_env_args(argv));
	print_env_vars(env);
	return (EXIT_SUCCESS);
}
