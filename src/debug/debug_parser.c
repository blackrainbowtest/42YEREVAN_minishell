/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:45:59 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/05 18:45:59 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void debug_print_cmds(t_cmd *cmds)
{
	int		i;
	t_redir	*r;

	while (cmds)
	{
		printf("=== Command ===\n");

		if (cmds->argv)
		{
			i = 0;
			while (cmds->argv[i])
			{
				printf("  argv[%d]: %s\n", i, cmds->argv[i]);
				i++;
			}
		}
		r = cmds->redir;
		while (r)
		{
			printf("  redir: type=%d, file=%s\n", r->type, r->file);
			r = r->next;
		}
		cmds = cmds->next;
		if (cmds)
			printf("--- PIPE ---\n");
	}
}