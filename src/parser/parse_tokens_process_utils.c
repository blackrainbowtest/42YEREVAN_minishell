/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_process_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:25:49 by aramarak          #+#    #+#             */
/*   Updated: 2025/11/13 19:28:39 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipe_redirection(t_token *tok)
{
	if (tok->next && (tok->next->type == T_HEREDOC
			|| tok->next->type == T_REDIR_IN
			|| tok->next->type == T_REDIR_OUT
			|| tok->next->type == T_REDIR_APPEND))
	{
		return (1);
	}
	return (0);
}
