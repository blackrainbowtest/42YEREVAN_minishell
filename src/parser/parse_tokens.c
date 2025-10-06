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

static int	process_token(t_cmd **cur, t_cmd **head,
			t_token **tok, t_env **locals)
{
	int	res;

	if ((*tok)->type == T_WORD || (*tok)->type == T_VAR
		|| (*tok)->type == T_DQUOTE || (*tok)->type == T_SQUOTE)
	{
		res = handle_word_token(*cur, *tok, locals);
		if (res < 0)
			return (-1);
		if (res == 1)
		{
			*tok = (*tok)->next;
			return (1);
		}
		return (0);
	}
	if ((*tok)->type == T_REDIR_IN || (*tok)->type == T_REDIR_OUT
		|| (*tok)->type == T_REDIR_APPEND || (*tok)->type == T_HEREDOC)
	{
		res = handle_redir_token(*cur, tok, *head);
		if (res < 0)
			return (-1);
		if (res == 1)
		{
			*tok = (*tok)->next;
			return (1);
		}
		return (0);
	}
	if ((*tok)->type == T_PIPE)
	{
		if (handle_pipe_token(cur, *head) < 0)
			return (-1);
	}
	return (0);
}

int	ensure_current_cmd(t_cmd **cur, t_cmd **head)
{
	if (!*cur)
	{
		*cur = new_cmd();
		if (!*cur)
			return (-1);
		if (!*head)
			*head = *cur;
	}
	return (0);
}

t_cmd	*parse_tokens(t_token *tokens, t_env **locals)
{
	t_cmd	*head = NULL;
	t_cmd	*cur = NULL;
	t_token	*tok = tokens;
	int		res;

	while (tok)
	{
		if (ensure_current_cmd(&cur, &head) < 0)
		{
			print_minishell_error("syntax error", NULL, "unexpected token", 2);
			return (NULL);
		}
		res = process_token(&cur, &head, &tok, locals);
		if (res < 0)
		{
			print_minishell_error("syntax error", NULL, "unexpected token", 2);
			last_status(1, 2);
			return (NULL);
		}
		if (res == 1)
			continue ;
		tok = tok->next;
	}
	return (head);
}

static void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free_argv(cmds->argv);
		free_redirs(cmds->redir);
		free(cmds);
		cmds = tmp;
	}
}