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

t_token	*tokenize(const char *line)
{
	t_token	*head;
	int		had_space;
	size_t	i;

	head = NULL;
	i = 0;
	while (line[i])
	{
		had_space = skip_whitespace(line, &i);
		if (!line[i])
			break;
		if (line[i] == '\'' || line[i] == '"')
			add_quoted_token(&head, line, &i, had_space);
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			add_operator_token(&head, line, &i, had_space);
		else if (line[i] == '$')
			add_var_token(&head, line, &i, had_space);
		else
			add_word_token(&head, line, &i, had_space);
	}
	return head;
}
