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

int	skip_whitespace(const char *line, size_t *i)
{
	int	skipped;

	skipped = 0;
	while (line[*i] == ' ' || line[*i] == '\t')
	{
		skipped = 1;
		(*i)++;
	}
	return (skipped);
}

void	add_quoted_token(t_token **head, const char *line,
		size_t *i, int had_space)
{
	t_token	*qtoken;

	qtoken = read_quoted(line, i);
	if (!qtoken)
		return ;
	qtoken->space_before = had_space;
	token_add_back(head, qtoken);
}

void	add_var_token(t_token **head, const char *line,
		size_t *i, int had_space)
{
	size_t	start;
	char	*token;
	t_token	*t;

	start = (*i)++;
	if (line[*i] == '?')
		(*i)++;
	else
		while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
			(*i)++;
	token = ft_substr(line, start, *i - start);
	if (!token)
		return ;
	t = new_token(token, T_VAR);
	if (t)
		t->space_before = had_space;
	token_add_back(head, t);
	free(token);
}

void	add_word_token(t_token **head, const char *line,
		size_t *i, int had_space)
{
	size_t	start;
	char	*token;
	t_token	*t;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
		&& line[*i] != '\'' && line[*i] != '"'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>'
		&& line[*i] != '$')
		(*i)++;
	token = ft_substr(line, start, *i - start);
	if (!token)
		return ;
	t = new_token(token, T_WORD);
	if (t)
		t->space_before = had_space;
	token_add_back(head, t);
	free(token);
}
