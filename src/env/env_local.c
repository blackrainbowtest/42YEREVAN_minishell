/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_local.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 22:30:12 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/25 01:31:01 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getlocal(t_env *locals, const char *key)
{
	while (locals)
	{
		if (ft_strncmp(locals->key, key, ft_strlen(key) + 1) == 0)
			return (locals->value);
		locals = locals->next;
	}
	return (NULL);
}

int	ft_setlocal(t_env **locals, const char *key,
	const char *value, int overwrite)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *locals;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
		{
			if (overwrite || !tmp->value)
			{
				free(tmp->value);
				tmp->value = ft_strdup(value);
			}
			return (0);
		}
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = *locals;
	*locals = new;
	return (0);
}

int	ft_unsetlocal(t_env **locals, const char *key)
{
	t_env	*cur;
	t_env	*prev;

	cur = *locals;
	prev = NULL;
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*locals = cur->next;
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

void	free_locals(t_env *locals)
{
	t_env	*tmp;

	while (locals)
	{
		tmp = locals->next;
		free(locals->key);
		free(locals->value);
		free(locals);
		locals = tmp;
	}
}

int	handle_assignment(t_env **locals, const char *token)
{
	char	*eq;
	char	*key;
	char	*value;
	int		res;

	eq = ft_strchr(token, '=');
	if (!eq)
		return (1);
	key = ft_substr(token, 0, eq - token);
	value = ft_strdup(eq + 1);
	res = ft_setlocal(locals, key, value, 1);
	free(key);
	free(value);
	return (res);
}
