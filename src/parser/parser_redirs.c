/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 22:36:31 by aramarak          #+#    #+#             */
/*   Updated: 2025/11/02 13:55:52 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parser_error(const char *msg, t_cmd *head)
{
	ft_putendl_fd((char *)msg, 2);
	free_cmds(head);
	return (-1);
}

static int	check_redir_syntax(t_token *tok, t_cmd *head)
{
	t_token	*next;

	next = tok->next;
	if (!next)
	{
		parser_error(MIN_OUT, head);
		last_status(1, 258);
		return (-2);
	}
	if (next->type == T_PIPE || next->type == T_REDIR_IN
		|| next->type == T_REDIR_OUT || next->type == T_REDIR_APPEND
		|| next->type == T_HEREDOC)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
		ft_putstr_fd((char *)token_to_str(next->type), 2);
		ft_putendl_fd("'", 2);
		free_cmds(head);
		last_status(1, 258);
		return (-2);
	}
	return (0);
}

static char	*collect_filename(t_token **tok)
{
	char	*filename;
	char	*tmp;

	filename = ft_strdup((*tok)->next->value);
	if (!filename)
		return (NULL);
	while ((*tok)->next->next && (*tok)->next->next->space_before == 0
		&& ((*tok)->next->next->type == T_WORD
			|| (*tok)->next->next->type == T_DQUOTE
			|| (*tok)->next->next->type == T_SQUOTE))
	{
		tmp = filename;
		filename = ft_strjoin(tmp, (*tok)->next->next->value);
		if (!filename)
		{
			free(tmp);
			return (NULL);
		}
		free(tmp);
		*tok = (*tok)->next;
	}
	return (filename);
}

static int	add_redirection_to_cmd(t_cmd *cur, t_redir_type rtype,
	char *filename, t_cmd *head)
{
	if (rtype == R_NONE)
		return (parser_error(MIN_UNKNOWN, head));
	if (add_redir(cur, rtype, filename) < 0)
	{
		free(filename);
		free_cmds(head);
		return (-1);
	}
	return (0);
}

int	handle_redir_token(t_cmd *cur, t_token **tok, t_cmd *head)
{
	t_redir_type	rtype;
	char			*filename;
	int				res;
	t_toktype		redir_tok_type;

	res = check_redir_syntax(*tok, head);
	if (res < 0)
		return (res);
	redir_tok_type = (*tok)->type;
	filename = collect_filename(tok);
	if (!filename)
		return (free_cmds(head), -1);
	rtype = token_to_redir_type(redir_tok_type);
	if (add_redirection_to_cmd(cur, rtype, filename, head) < 0)
		return (free(filename), -1);
	free(filename);
	*tok = (*tok)->next;
	return (1);
}
