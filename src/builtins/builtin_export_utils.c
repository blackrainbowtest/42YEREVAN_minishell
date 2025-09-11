/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 11:32:04 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/07 15:35:19 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_update_env(char *arg, t_env **env, char *eq, int *status)
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

int env_size(t_env *env)
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

char	**env_to_keys(t_env *env)
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

void	sort_env_keys(char **keys)
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

void	print_sorted_env(t_env *env, char **keys)
{
	int		i;
	t_env	*cur;

	i = 0;
	while (keys[i])
	{
		cur = env;
		while (cur)
		{
			if (ft_strcmp(cur->key, keys[i]) == 0)
			{
				if (cur->value)
					printf("declare -x %s=\"%s\"\n", cur->key, cur->value);
				else
					printf("declare -x %s\n", cur->key);
				break ;
			}
			cur = cur->next;
		}
		i++;
	}
}
