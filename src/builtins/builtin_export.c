/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:38:56 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/03 19:38:56 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_no_arguments(char **argv, t_env **env)
{
	t_env	*cur;

	(void)argv;
	cur = *env;
	while (cur)
	{
		if (cur->value)
			printf("declare -x %s=\"%s\"\n", cur->key, cur->value);
		else
			printf("declare -x %s\n", cur->key);
		cur = cur->next;
	}
	return (0);
}

static void	export_update_env(char *arg, t_env **env, char *eq, int *status)
{
	char	*key;
	char	*value;

	if (eq)
	{
		key = ft_substr(arg, 0, eq - arg);
		value = ft_strdup(eq + 1);
		if (!key || !value || ft_setenv(env, key, value, 1) != 0)
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putendl_fd(": allocation error", 2);
			*status = 1;
		}
		free(key);
		free(value);
	}
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
		return (export_no_arguments(argv, env));
	return (export_with_arguments(argv, env));
}
