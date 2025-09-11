/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:52:48 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/11 19:53:10 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **env_to_envp(t_env *env)
{
	int		count;
	t_env	*tmp;
	char	**envp;
	char	*pair;
	int		i;
	size_t	len;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		len = ft_strlen(tmp->key) + 1 + (tmp->value ? strlen(tmp->value) : 0);
		pair = malloc(len + 1);
		if (!pair)
			return (NULL);
		ft_strlcpy(pair, tmp->key, len + 1);
		ft_strlcat(pair, "=", len + 1);
		if (tmp->value)
			ft_strlcat(pair, tmp->value, len + 1);
		envp[i++] = pair;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}