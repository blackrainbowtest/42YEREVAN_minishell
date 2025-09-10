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

static int env_size(t_env *env)
{
	int count;

	count = 0;
	if (NULL == env)
		return (count);
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static char	**env_to_keys(t_env *env)
{
	int		count;
	char	**keys;
	int		i;

	count = env_size(env);
	keys = malloc(sizeof(char *) * (count + 1));
	if (!keys)
		return (NULL);
	i = 0;
	while (env)
	{
		keys[i] = ft_strdup(env->key);
		if (!keys[i])
		{
			while (i > 0)
				free(keys[--i]);
			free(keys);
		}
		i++;
		env = env->next;
	}
	keys[i] = NULL;
	return (keys);
}

static void	sort_env_keys(char **keys)
{
	int		i;
	int		j;
	char	*tmp;

	if (!keys)
		return ;
	i = 0;
	while (keys[i])
	{
		j = i + 1;
		while (keys[j])
		{
			if (ft_strcmp(keys[i], keys[j]) > 0)
			{
				tmp = keys[i];
				keys[i] = keys[j];
				keys[j] = tmp;
			}
			++j;
		}
		++i;
	}
}

static int	export_no_arguments(char **argv, t_env **env)
{
	char	**keys;
	int		i;

	void(argv);
	keys = env_to_keys(*env);
	if (!keys)
		return (EXIT_FAILURE);
	sort_env_keys(keys);
	i = 0;
	while (keys[i])
	{

	}
	free(keys);
	return (EXIT_SUCCESS);
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
