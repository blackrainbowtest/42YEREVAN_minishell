/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 00:10:15 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/24 00:39:48 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_var_token(t_token *tok, t_env *env)
{
	char	*expanded;

	expanded = expand_string(tok->value, env);
	free(tok->value);
	tok->value = expanded;
}

void	expand_word_token(t_token *tok, t_env *env)
{
	char	*expanded;

	expanded = expand_string(tok->value, env);
	free(tok->value);
	tok->value = expanded;
}

void	expand_dquote_token(t_token *tok, t_env *env)
{
	char	*expanded;

	expanded = expand_string(tok->value, env);
	free(tok->value);
	tok->value = expanded;
}

void	append_char(char **result, char c)
{
	char	buf[2];
	char	*new;

	buf[1] = 0;
	buf[0] = c;
	new = ft_strjoin(*result, buf);
	free(*result);
	*result = new;
}

void	append_str(char **result, const char *s)
{
	char	*new;

	new = ft_strjoin(*result, s);
	free(*result);
	*result = new;
}
