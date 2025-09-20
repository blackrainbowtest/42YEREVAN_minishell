/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:01:26 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/20 16:42:54 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_variables(t_cmd *cmds, t_env *env)
{
	t_cmd	*cmd;
	int		i;
	char	*expanded;

	cmd = cmds;
	while (cmd)
	{
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			if (cmd->argv[i][0] == '$')
			{
				expanded = expand_one(cmd->argv[i], env);
				if (expanded)
				{
					free(cmd->argv[i]);
					cmd->argv[i] = expanded;
				}
			}
			i++;
		}
		cmd = cmd->next;
	}
}

char	*expand_one(char *arg, t_env *env)
{
	char	*name;
	char	*value;

	if (ft_strcmp(arg, "$?") == 0)
		return (ft_itoa(last_status(0, 0)));

	if (arg[0] == '$' && arg[1])
	{
		name = arg + 1;
		value = ft_getenv(env, name);
		if (value)
			return (ft_strdup(value));
		return (ft_strdup(""));
	}
	return (ft_strdup(arg));
}
