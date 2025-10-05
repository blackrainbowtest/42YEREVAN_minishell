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
		fd = -1;
		if (r->file == NULL || r->file[0] == '\0')
		{
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			return (-1);
		}
		printf("r->type = %d, R_IN = %d, r->file = \"%s\"\n", r->type, R_IN, r->file);
		if (r->type == R_IN)
			fd = open(r->file, O_RDONLY);
		else if (r->type == R_OUT)
			fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (r->type == R_APPEND)
			fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (r->type == R_HEREDOC)
			fd = open_heredoc(r->file);
		printf("%d\n", fd);
		if (fd < 0)
		{
			perror(r->file);
			return (-1);
		}
		if (is_input_redir(r))
		{
			if (dup2(fd, STDIN_FILENO) < 0)
			{
				perror("dup2");
				close(fd);
				return (-1);
			}
		}
		else if (is_output_redir(r))
		{
			if (dup2(fd, STDOUT_FILENO) < 0)
			{
				perror("dup2");
				close(fd);
				return (-1);
			}
		}
		close(fd);
		r = r->next;
	}
	return (0);
}

