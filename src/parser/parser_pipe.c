/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:36:13 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/13 14:38:52 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->argv)
			free_argv(cmds->argv);
		if (cmds->infile)
			free(cmds->infile);
		if (cmds->outfile)
			free(cmds->outfile);
		free(cmds);
		cmds = tmp;
	}
}
