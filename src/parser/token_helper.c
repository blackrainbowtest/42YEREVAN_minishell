/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:27:13 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/11 20:27:26 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_whitespace(const char *line, size_t *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

void	add_quoted_token(t_token **head, const char *line, size_t *i)
{
	t_token	*qtoken;

	qtoken = read_quoted(line, i);
	if (!qtoken)
		return ;
	token_add_back(head, qtoken);
}

void	add_operator_token(t_token **head, const char *line, size_t *i)
{
	if (line[*i] == '|' )
	{
		token_add_back(head, new_token("|", T_PIPE));
		(*i)++;
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		token_add_back(head, new_token("<<", T_HEREDOC));
		(*i) += 2;
	}
	else if (line[*i] == '<')
	{
		token_add_back(head, new_token("<", T_REDIR_IN));
		(*i)++;
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		token_add_back(head, new_token(">>", T_REDIR_APPEND));
		(*i) += 2;
	}
	else if (line[*i] == '>')
	{
		token_add_back(head, new_token(">", T_REDIR_OUT));
		(*i)++;
	}
}

void	add_var_token(t_token **head, const char *line, size_t *i)
{
	size_t	start;
	char	*token;

	start = (*i)++;
	if (line[*i] == '?')
		(*i)++;
	else
		while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
			(*i)++;
	token = ft_substr(line, start, *i - start);
	token_add_back(head, new_token(token, T_VAR));
	free(token);
}

void	add_word_token(t_token **head, const char *line, size_t *i)
{
	size_t	start;
	char	*token;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
		&& line[*i] != '\'' && line[*i] != '"'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>'
		&& line[*i] != '$')
		(*i)++;

	token = ft_substr(line, start, *i - start);
	token_add_back(head, new_token(token, T_WORD));
	free(token);
}
