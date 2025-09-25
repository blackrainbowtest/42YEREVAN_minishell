/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:01:26 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/25 19:57:08 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_tokens(t_token *tokens, t_env *env, t_env *locals)
{
	t_token	*tok;
(void)locals;
	if (DEBUGING)
	{
		printf("Before expansion:\n");
		debug_print_tokens(tokens);
	}
	tok = tokens;
	while (tok)
	{
		if (tok->type == T_VAR)
			expand_var_token(tok, env);
		else if (tok->type == T_WORD)
			expand_word_token(tok, env);
		else if (tok->type == T_DQUOTE)
			expand_dquote_token(tok, env);
		tok = tok->next;
	}
	if (DEBUGING)
	{
		printf("After expansion:\n");
		debug_print_tokens(tokens);
	}
}

static char	*expand_status(size_t *i)
{
	char	*tmp;

	tmp = ft_itoa(last_status(0, 0));
	(*i)++;
	return (tmp);
}

static char	*expand_env_var(const char *str, size_t start, size_t end,
	t_env *env)
{
	char	*name;
	char	*val;

	name = ft_substr(str, start, end - start);
	val = ft_getenv(env, name);
	free(name);
	if (val)
		return (ft_strdup(val));
	else
		return (ft_strdup(""));
}

static char	*expand_dollar(const char *str, size_t *i, t_env *env)
{
	size_t	start;

	start = ++(*i);
	if (!str[*i])
		return (ft_strdup("$"));
	if (str[*i] == '?')
		return (expand_status(i));
	else
	{
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
		return (expand_env_var(str, start, *i, env));
	}
}

char	*expand_string(const char *str, t_env *env)
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
			expanded = expand_dollar(str, &i, env);
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
