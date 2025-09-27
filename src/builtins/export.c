/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:38:56 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/03 19:38:56 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_no_arguments(t_env **env)
{
	char	**keys;

	keys = env_to_keys(*env);
	if (!keys)
		return (print_minishell_error("export", NULL, ERR_MEM_ALLOC, 1));
	sort_env_keys(keys);
	print_sorted_env(*env, keys);
	ft_free_split(keys);
	return (last_status(1, 0));
}

static int	export_with_arguments(char **argv, t_env **env)
{
	int		status;
	int		i;
	char	*eq;

	status = 0;
	i = 1;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			print_minishell_error("export", argv[i], ERR_NT_VAL_INP, 1);
			status = 1;
			i++;
			continue ;
		}
		eq = ft_strchr(argv[i], '=');
		if (eq)
			export_update_env(argv[i], env, eq, &status);
		else
		{
			if (ft_setenv(env, argv[i], "", 0) != 0)
			{
				print_minishell_error("export", argv[i], ERR_CT_ALLOC_MEM, 1);
				status = 1;
			}
		}
		i++;
	}
	last_status(1, status);
	return (status);
}

int	builtin_export(char **argv, t_env **env)
{
	if (!argv[1])
		return (export_no_arguments(env));
	return (export_with_arguments(argv, env));
}
