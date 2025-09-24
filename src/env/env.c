/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 13:19:23 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/06 13:19:23 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

static t_env	*create_env_node(char *entry)
{
	t_env	*new;
	char	*eq;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	eq = ft_strchr(entry, '=');
	if (eq)
	{
		new->key = ft_substr(entry, 0, eq - entry);
		new->value = ft_strdup(eq + 1);
	}
	else
	{
		new->key = ft_strdup(entry);
		new->value = NULL;
	}
	new->next = NULL;
	return (new);
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*new;

	head = NULL;
	while (*envp)
	{
		new = create_env_node(*envp);
		if (!new)
			return (NULL);
		new->next = head;
		head = new;
		envp++;
	}
	return (head);
}
