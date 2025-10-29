/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:33:11 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/15 19:34:44 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc_signals.h"

static void	ignore_heredoc_signals(struct sigaction *old_int,
							struct sigaction *old_quit)
{
	struct sigaction	sa_ignore;

	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sa_ignore.sa_handler = SIG_IGN;
	sigaction(SIGINT, NULL, old_int);
	sigaction(SIGQUIT, NULL, old_quit);
	sigaction(SIGINT, &sa_ignore, NULL);
	sigaction(SIGQUIT, &sa_ignore, NULL);
}

static void	restore_heredoc_signals(const struct sigaction *old_int,
							const struct sigaction *old_quit)
{
	sigaction(SIGINT, old_int, NULL);
	sigaction(SIGQUIT, old_quit, NULL);
}

static int	open_and_store_heredoc(t_redir *r)
{
	int	fd;

	fd = open_heredoc(r->file);
	if (fd < 0)
		return (-1);
	r->fd = fd;
	return (0);
}

static int	process_heredoc_redirs(t_redir *redir)
{
	t_redir	*r;

	r = redir;
	while (r)
	{
		if (r->type == R_HEREDOC)
		{
			int fd = open_heredoc(r->file);
			if (fd < 0)
				return (-1);
			r->fd = fd;
		}
		r = r->next;
	}
	return (0);
}

int	prepare_heredocs(t_cmd *cmds)
{
	struct sigaction	old_int;
	struct sigaction	old_quit;
	t_cmd *cur;

	ignore_heredoc_signals(&old_int, &old_quit);
	cur = cmds;
	while (cur)
	{
		if (process_heredoc_redirs(cur->redir) < 0)
		{
			restore_heredoc_signals(&old_int, &old_quit);
			return (-1);
		}
		cur = cur->next;
	}
	restore_heredoc_signals(&old_int, &old_quit);
	return (0);
}
