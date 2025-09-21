/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:01:26 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/20 20:55:10 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_tokens(t_token *tokens, t_env *env)
{
	t_token	*tok;
	char	*expanded;

	tok = tokens;
	while (tok)
	{
		if (tok->value && tok->value[0] == '$')
		{
			expanded = expand_one(tok->value, env);
			if (expanded)
			{
				free(tok->value);
				tok->value = expanded;
			}
		}
		tok = tok->next;
	}
}

char	*expand_one(char *arg, t_env *env)
{
	char	*name;
	char	*value;

	if (ft_strcmp(arg, "$?") == 0)
		return (ft_itoa(last_status(0, 0)));
	if (arg[0] == '$' && arg[1])
	{
		name = arg + 1;
		value = ft_getenv(env, name);
		if (value)
			return (ft_strdup(value));
		return (ft_strdup(""));
	}
	return (ft_strdup(arg));
}
