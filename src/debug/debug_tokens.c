/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 00:02:38 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/24 00:53:54 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*toktype_to_str(t_toktype type)
{
	if (type == T_WORD)
		return ("WORD");
	if (type == T_SQUOTE)
		return ("SQUOTE");
	if (type == T_DQUOTE)
		return ("DQUOTE");
	if (type == T_VAR)
		return ("VAR");
	if (type == T_PIPE)
		return ("PIPE");
	if (type == T_REDIR_IN)
		return ("REDIR_IN");
	if (type == T_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == T_REDIR_APPEND)
		return ("REDIR_APPEND");
	if (type == T_HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

void	debug_print_tokens(t_token *tokens)
{
	t_token	*tok;
	int		i;

	tok = tokens;
	i = 0;
	while (tok)
	{
		printf("[%02d] type=\033[33m%s\033[0m, space_before=%d,
			value=\033[32m'%s'\033[0m\n", i, toktype_to_str(tok->type),
			tok->space_before, tok->value);
		tok = tok->next;
		i++;
	}
}
