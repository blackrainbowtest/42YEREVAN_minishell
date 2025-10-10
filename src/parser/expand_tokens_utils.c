/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 23:23:45 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/10 23:28:05 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_dollar(const char *str,
	size_t *i, t_env *env, t_env *locals)
{
	size_t	start;
	char	*val;

	start = ++(*i);
	if (!str[*i])
		return (ft_strdup("$"));
	if (str[*i] == '?')
		return (expand_status(i));
	else if (!ft_isalnum(str[*i]) && str[*i] != '_')
	{
		return (ft_strdup("$"));
	}
	else
	{
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
		val = expand_local_env_var(str, start, *i, locals);
		if (!val)
			val = expand_env_var(str, start, *i, env);
		if (!val)
			return (ft_strdup(""));
		return (val);
	}
	(void)env;
}

char	*expand_string(const char *str, t_env *env, t_env *locals)
{
	size_t	i;
	char	*result;
	char	*expanded;

	i = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			expanded = expand_dollar(str, &i, env, locals);
			append_str(&result, expanded);
			free(expanded);
		}
		else
		{
			append_char(&result, str[i]);
			i++;
		}
	}
	return (result);
}
