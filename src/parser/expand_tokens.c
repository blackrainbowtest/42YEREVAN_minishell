/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:01:26 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/10 23:27:55 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_status(size_t *i)
{
	char	*tmp;

	tmp = ft_itoa(last_status(0, 0));
	(*i)++;
	return (tmp);
}

char	*expand_env_var(const char *str, size_t start, size_t end,
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

char	*expand_local_env_var(const char *str,
	size_t start, size_t end, t_env *locals)
{
	char	*name;
	char	*val;

	name = ft_substr(str, start, end - start);
	if (!name)
		return (NULL);
	val = ft_getlocal(locals, name);
	free(name);
	if (val)
		return (ft_strdup(val));
	return (NULL);
}

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
			expand_var_token(tok, env, locals);
		else if (tok->type == T_WORD)
			expand_word_token(tok, env, locals);
		else if (tok->type == T_DQUOTE)
			expand_dquote_token(tok, env, locals);
		tok = tok->next;
	}
	if (DEBUGING)
	{
		printf("After expansion:\n");
		debug_print_tokens(tokens);
	}
}
