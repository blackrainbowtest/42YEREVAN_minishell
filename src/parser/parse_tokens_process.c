/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:06:08 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/16 20:09:24 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_word_or_var(t_cmd *cur, t_token **tok, t_env **locals)
{
	int	res;

	res = handle_word_token(cur, *tok, locals);
	if (res < 0)
		return (-1);
	if (res == 1)
	{
		*tok = (*tok)->next;
		return (1);
	}
	return (0);
}

static int	handle_redirection(t_cmd *cur, t_cmd *head, t_token **tok)
{
	int	res;

	res = handle_redir_token(cur, tok, head);
	if (res < 0)
		return (-1);
	if (res == 1)
	{
		*tok = (*tok)->next;
		return (1);
	}
	return (0);
}

int	process_token(t_cmd **cur, t_cmd **head, t_token **tok, t_env **locals)
{
	if ((*tok)->type == T_WORD || (*tok)->type == T_VAR
		|| (*tok)->type == T_DQUOTE || (*tok)->type == T_SQUOTE)
		return (handle_word_or_var(*cur, tok, locals));
	if ((*tok)->type == T_REDIR_IN || (*tok)->type == T_REDIR_OUT
		|| (*tok)->type == T_REDIR_APPEND || (*tok)->type == T_HEREDOC)
		return (handle_redirection(*cur, *head, tok));
	if ((*tok)->type == T_PIPE)
	{
		if (handle_pipe_token(cur, *head) < 0)
			return (-1);
	}
	return (0);
}
