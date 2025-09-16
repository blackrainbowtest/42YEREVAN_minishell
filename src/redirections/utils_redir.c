/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:40:33 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/14 16:59:06 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_input_redir(t_redir *r)
{
	if (!r)
		return (0);
	return (r->type == R_IN || r->type == R_HEREDOC);
}

int	is_output_redir(t_redir *r)
{
	if (!r)
		return (0);
	return (r->type == R_OUT || r->type == R_APPEND);
}
