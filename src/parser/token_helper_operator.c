/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper_operator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:43:58 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/30 23:28:05 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*get_redir_token(const char *line, size_t *i)
{
	if (line[*i] == '<' && line[*i + 1] && line[*i + 1] == '<')
	{
		*i += 2;
		return (new_token("<<", T_HEREDOC));
	}
	if (line[*i] == '<')
	{
		(*i)++;
		return (new_token("<", T_REDIR_IN));
	}
	if (line[*i] == '>' && line[*i + 1] && line[*i + 1] == '>')
	{
		*i += 2;
		return (new_token(">>", T_REDIR_APPEND));
	}
	if (line[*i] == '>')
	{
		(*i)++;
		return (new_token(">", T_REDIR_OUT));
	}
	return (NULL);
}

static t_token	*get_operator_token(const char *line, size_t *i)
{
	if (line[*i] == '|')
	{
		(*i)++;
		return (new_token("|", T_PIPE));
	}
	return (NULL);
}

void	add_operator_token(t_token **head, const char *line,
		size_t *i, int had_space)
{
	t_token	*t;

	t = get_operator_token(line, i);
	if (!t)
		t = get_redir_token(line, i);
	if (t)
	{
		t->space_before = had_space;
		token_add_back(head, t);
	}
}
