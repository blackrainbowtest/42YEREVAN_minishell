/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:06:08 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/31 00:27:02 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_syntax_error(t_cmd *head, const char *token)
{
	if (!token)
		token = "newline";
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd((char *)token, 2);
	ft_putendl_fd("'", 2);
	free_cmds(head);
	last_status(1, 258);
	return (-2);
}

static int	validate_pipe(t_cmd *cur, t_cmd *head, t_token *tok)
{
	t_token	*next;

	if (!cur->argv || !cur->argv[0])
		return (pipe_syntax_error(head, token_to_str(tok->type)));
	next = tok->next;
	if (!next)
		return (pipe_syntax_error(head, "newline"));
	while (next && (next->type == T_REDIR_IN || next->type == T_REDIR_OUT
			|| next->type == T_REDIR_APPEND || next->type == T_HEREDOC))
	{
		if (!next->next)
			return (pipe_syntax_error(head, "newline"));
		next = next->next->next;
	}
	if (!next)
		return (pipe_syntax_error(head, "newline"));
	if (next->type == T_PIPE)
		return (pipe_syntax_error(head, token_to_str(next->type)));
	if (next->type != T_WORD && next->type != T_VAR
		&& next->type != T_DQUOTE && next->type != T_SQUOTE)
		return (pipe_syntax_error(head, token_to_str(next->type)));
	return (0);
}

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
		return (res);
	if (res == 1)
	{
		*tok = (*tok)->next;
		return (res);
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
		if (validate_pipe(*cur, *head, *tok) < 0)
			return (-2);
		if (handle_pipe_token(cur, *head) < 0)
			return (-1);
	}
	return (0);
}
