/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:36:13 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/16 20:10:26 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipe_token(t_cmd **cur, t_cmd *head)
{
	(*cur)->next = new_cmd();
	if (!(*cur)->next)
	{
		free_cmds(head);
		return (-1);
	}
	*cur = (*cur)->next;
	return (0);
}

const char	*token_to_str(t_toktype type)
{
	if (type == T_PIPE)
		return ("|");
	if (type == T_REDIR_IN)
		return ("<");
	if (type == T_REDIR_OUT)
		return (">");
	if (type == T_REDIR_APPEND)
		return (">>");
	if (type == T_HEREDOC)
		return ("<<");
	return ("?");
}

t_redir_type	token_to_redir_type(t_toktype type)
{
	if (type == T_REDIR_IN)
		return (R_IN);
	if (type == T_REDIR_OUT)
		return (R_OUT);
	if (type == T_REDIR_APPEND)
		return (R_APPEND);
	if (type == T_HEREDOC)
		return (R_HEREDOC);
	return (R_NONE);
}
