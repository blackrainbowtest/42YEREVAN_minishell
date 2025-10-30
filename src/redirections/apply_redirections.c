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

static int	open_target_file(t_redir *r)
{
	if (r->type == R_IN)
		return (open(r->file, O_RDONLY));
	else if (r->type == R_OUT)
		return (open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (r->type == R_APPEND)
		return (open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else if (r->type == R_HEREDOC)
		return (r->fd);
	return (-1);
}

static int	apply_single_redir(t_redir *r)
{
	int	fd;
	int	target;

	fd = open_target_file(r);
	if (fd < 0)
	{
		if (r->type == R_HEREDOC)
		{
			ft_putstr_fd("minishell: failed to open heredoc for `", 2);
			ft_putstr_fd(r->file, 2);
			ft_putendl_fd("'", 2);
		}
		else
			perror(r->file);
		return (-1);
	}
	if (is_input_redir(r))
		target = STDIN_FILENO;
	else
		target = STDOUT_FILENO;
	if (dup2(fd, target) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;

	if (!cmd)
		return (-1);
	r = cmd->redir;
	while (r)
	{
		if (!r->file || r->file[0] == '\0')
		{
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			return (-1);
		}
		if (apply_single_redir(r) < 0)
			return (-1);
		r = r->next;
	}
	return (0);
}
