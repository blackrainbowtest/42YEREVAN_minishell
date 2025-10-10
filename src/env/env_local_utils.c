/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_local_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 23:37:17 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/10 21:47:16 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getvar(t_env *locals, t_env *env, const char *key)
{
	while (locals)
	{
		if (ft_strncmp(locals->key, key, ft_strlen(key) + 1) == 0)
			return (locals->value);
		locals = locals->next;
	}
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static void	delete_local_node(t_env **locals, t_env *cur, t_env *prev)
{
	if (prev)
		prev->next = cur->next;
	else
		*locals = cur->next;
	free(cur->key);
	free(cur->value);
	free(cur);
}

static int	set_env_var(t_env **env, const char *key, const char *value)
{
	char	*val;

	if (value)
		val = ft_strdup(value);
	else
		val = ft_strdup("");
	if (!val)
		return (1);
	ft_setenv(env, key, val, 1);
	free(val);
	return (0);
}

int	move_local_to_env(t_env **locals, t_env **env, const char *key)
{
	t_env	*cur;
	t_env	*prev;

	cur = *locals;
	prev = NULL;
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(key) + 1) == 0)
		{
			if (set_env_var(env, cur->key, cur->value))
				return (1);
			delete_local_node(locals, cur, prev);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}

int	is_assignment_token(const char *str)
{
	int	i;

	i = 0;
	if ((!str) || ((!ft_isalpha(str[0])) && (str[0] != '_')))
		return (0);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (str[i] == '=')
		return (1);
	return (0);
}
