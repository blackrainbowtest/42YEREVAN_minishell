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
		// we skip spaces and tabs after command
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		// ☢ if no more symbols left exit loot here
		if (line[i])
			break ;
		start = i;
		while (line[i] && line[i] != ' ' && line[i] != '\t')
			i++;
		// create and add new token using start and end position
		token_add_back(&head, new_token(&line[start], i - start));
	}
	return (head);
}
