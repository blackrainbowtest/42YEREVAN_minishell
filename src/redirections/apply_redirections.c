/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:40:33 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/14 16:59:06 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * TODO: in feature need add dup2(fd, STDIN_FILENO/STDOUT_FILENO) 
 * depending on the type.
 */
int	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	if (!cmd)
		return (-1);
	r = cmd->redir;
	while (r)
	{
		if (r->type == R_IN)
			fd = open_read(r->file);
		else if (r->type == R_OUT)
			fd = open_trunc(r->file);
		else if (r->type == R_APPEND)
			fd = open_append(r->file);
		else if (r->type == R_HEREDOC)
			fd = open_heredoc(r->file);
		else
			fd = -1;

		if (fd < 0)
		{
			ft_putstr_fd(" No such file or directory\n", 2);
			return (-1);
		}

		if (is_input_redir(r))
			dup2(fd, STDIN_FILENO);
		else if (is_output_redir(r))
			dup2(fd, STDOUT_FILENO);

		close(fd);
		r = r->next;
	}
	return (0);
}
