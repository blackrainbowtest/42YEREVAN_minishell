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
		return (EXIT_FAILURE);
	sort_env_keys(keys);
	print_sorted_env(*env, keys);
	ft_free_split(keys);
	return (EXIT_SUCCESS);
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
		eq = ft_strchr(argv[i], '=');
		if (eq)
			export_update_env(argv[i], env, eq, &status);
		else
		{
			if (ft_setenv(env, argv[i], "", 0) != 0)
			{
				fprintf(stderr, EXP_AERR, argv[i]);
				status = 1;
			}
		}
		i++;
	}
	return (status);
}

int	builtin_export(char **argv, t_env **env)
{
	if (!argv[1])
		return (export_no_arguments(env));
	return (export_with_arguments(argv, env));
}
