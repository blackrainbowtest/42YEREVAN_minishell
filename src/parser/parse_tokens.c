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

static int	syntax_error(void)
{
	print_minishell_error("syntax error", NULL, "unexpected token", 2);
	return (-1);
}

t_cmd	*parse_tokens(t_token *tokens, t_env **locals)
{
	t_cmd	*head;
	t_cmd	*cur;
	t_token	*tok;
	int		res;

	head = NULL;
	cur = NULL;
	tok = tokens;
	while (tok)
	{
		if (ensure_current_cmd(&cur, &head) < 0)
			return (syntax_error(), NULL);
		res = process_token(&cur, &head, &tok, locals);
		if (res < 0)
			return (syntax_error(), NULL);
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
