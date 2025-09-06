/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:45:59 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/05 18:45:59 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

char	*ft_getenv(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	ft_setenv(t_env **env, const char *key, const char *value, int overwrite)
{
	t_env	*tmp;
	t_env	*new_env;

	tmp = *env;
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0) // LIBFT
		{
			if (overwrite || !tmp->value)
			{
				free(tmp->value);
				tmp->value = strdup(value); // LIBFT
			}
			return (0);
		}
		tmp = tmp->next;
	}
	new_env = malloc(sizeof(t_env));
	if (NULL == new_env)
		return (1);
	new_env->key = strdup(key); // LIBFT
	new_env->value = strdup(value); // LIBFT
	new_env->next = *env;
	env = new_env;
	return (0);
}

int ft_unsetenv(t_env **env, const char *key)
{
	t_env	*cur;
	t_env	*prev;

	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (strcmp(cur-key, key) == 0) // LIBFT
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (1);
}
