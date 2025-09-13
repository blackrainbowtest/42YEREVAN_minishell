/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:08:40 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/13 21:36:19 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pipeline(t_cmd *cmds, t_env *env)
{
	t_cmd	*cur;
	int		ncmds;

	ncmds = 0;
	cur = cmds;
	while (cur)
	{
		ncmds++;
		cur = cur->next;
	}
	if (ncmds == 1)
	{
		return (execute_command(cmds->argv, env));
	}
	// 2. Pipe logic will be here:
	// - create pipe()
	// - fork processes
	// - configure dup2
	// - close descriptors
	// - wait for children (waitpid)

	// For now, let's return 0 as a stub 
	return (0);
}
