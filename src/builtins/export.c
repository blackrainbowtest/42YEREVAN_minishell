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

int	builtin_export(char **argv, t_env **env)
{
	if (!argv[1])
		return (export_no_arguments(env));
	return (export_with_arguments(argv, env));
}

static void	print_env_entry(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			if (env->value)
				printf("declare -x %s=\"%s\"\n", env->key, env->value);
			else
				printf("declare -x %s\n", env->key);
			return ;
		}
		env = env->next;
	}
}

void	print_sorted_env(t_env *env, char **keys)
{
	int	i;

	i = 0;
	while (keys[i])
	{
		if (ft_strcmp(keys[i], "_") != 0)
			print_env_entry(env, keys[i]);
		i++;
	}
}
