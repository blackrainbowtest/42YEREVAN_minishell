/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:27:13 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/11 20:27:26 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_toktype	get_quote_type(char quote)
{
	if (quote == '\'')
		return (T_SQUOTE);
	return (T_DQUOTE);
}

size_t	get_quoted_length(const char *line, size_t start, char quote)
{
	size_t	i;

	i = start;
	while (line[i] && line[i] != quote)
		i++;
	if (!line[i])
		return ((size_t) - 1);
	return (i - start);
}

t_token	*handle_unclosed_quote(char quote)
{
	fprintf(stderr, ERR_SYN_EOF, quote);
	last_status(1, 2);
	return (NULL);
}

t_token	*read_quoted(const char *line, size_t *i)
{
	size_t		start;
	size_t		len;
	char		*substr;
	t_toktype	type;
	t_token		*tok;

	type = get_quote_type(line[*i]);
	start = ++(*i);
	len = get_quoted_length(line, *i, line[start - 1]);
	if (len == (size_t)-1)
		return (handle_unclosed_quote(line[start - 1]));
	substr = ft_substr(line, start, len);
	if (!substr)
		return (NULL);
	tok = new_token(substr, type);
	free(substr);
	*i += len + 1;
	return (tok);
}
