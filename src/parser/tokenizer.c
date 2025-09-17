/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:27:13 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/11 20:27:26 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*new_token(const char *str, size_t len)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_substr(str, 0, len);
	if (!token->value)
		return (free(token), NULL);
	token->next = NULL;
	return (token);
}

static void	token_add_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static char	*read_quoted(const char *line, size_t *i)
{
	char	quote;
	size_t	start;
	size_t	len;
	char	*token;

	// its " or '
	quote = line[*i];
	// skip first quote
	(*i)++;
	start = *i;
	// loop while str not end or we not found quote
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
		return (NULL);
	// to get length we can subtract start from end
	len = *i - start;
	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, line + start, len + 1);
	(*i)++;
	// skip closed quote symbol
	return (token);
}

void free_tokens(t_token *lst)
{
    t_token *tmp;

    while (lst)
    {
        tmp = lst->next;
        free(lst->value);
        free(lst);
        lst = tmp;
    }
}

char	**tokenize(const char *line)
{
	t_token	*head;
	size_t	i;
	size_t	start;

	head = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (!line[i])
			break ;
		if (line[i] == '\'' || line[i] == '"')
		{
			char *q = read_quoted(line, &i);
			if (!q)
				return (free_tokens(head), NULL);
			token_add_back(&head, new_token(q, ft_strlen(q)));
			free(q);
		}
		else
		{
			start = i;
			while (line[i] && line[i] != ' ' && line[i] != '\t'
				&& line[i] != '\'' && line[i] != '"')
				i++;
			token_add_back(&head, new_token(&line[start], i - start));
		}
	}
	return (head);
}
