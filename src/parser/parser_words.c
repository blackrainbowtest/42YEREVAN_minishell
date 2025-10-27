/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 22:34:29 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/24 22:55:16 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

static int	handle_assignment_if_needed(t_cmd *cur, t_token *tok,
		t_env **locals)
{
	if (is_assignment_token(tok->value) && !cur->argv)
	{
		handle_assignment(locals, tok->value);
		return (1);
	}
	return (0);
}

static int	append_or_add_arg(t_cmd *cur, t_token *tok, int last_idx)
{
	char	*old;

	if (tok->space_before == 0 && last_idx >= 0)
	{
		old = cur->argv[last_idx];
		cur->argv[last_idx] = ft_strjoin(old, tok->value);
		free(old);
		return (0);
	}
	if (tok->value)
	{
		if (add_arg(cur, tok->value) < 0)
			return (-1);
	}
	else
	{
		if (add_arg(cur, "") < 0)
			return (-1);
	}
	return (0);
}

int	handle_word_token(t_cmd *cur, t_token *tok, t_env **locals)
{
	int	last_idx;
	int	assign_check;

	if (!tok->value)
		tok->value = ft_strdup("");
	assign_check = handle_assignment_if_needed(cur, tok, locals);
	if (assign_check != 0)
		return (assign_check);
	last_idx = ft_arrlen(cur->argv) - 1;
	return (append_or_add_arg(cur, tok, last_idx));
}
