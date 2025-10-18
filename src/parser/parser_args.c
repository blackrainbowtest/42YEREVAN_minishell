/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 22:32:48 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/18 22:33:26 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **argv)
{
	int	count;

	count = 0;
	if (argv)
		while (argv[count])
			count++;
	return (count);
}

static char	**extend_argv(char **argv, int argc, const char *value)
{
	char	**new_argv;
	int		i;

	new_argv = malloc(sizeof(char *) * (argc + 2));
	if (!new_argv)
		return (NULL);
	i = 0;
	while (i < argc)
	{
		new_argv[i] = argv[i];
		i++;
	}
	if (value == NULL)
		new_argv[argc] = ft_strdup("");
	else
		new_argv[argc] = ft_strdup(value);
	if (!new_argv[argc])
		return (free(new_argv), NULL);
	new_argv[argc + 1] = NULL;
	return (new_argv);
}

int	add_arg(t_cmd *cmd, const char *value)
{
	int		argc;
	char	**new_argv;

	argc = count_args(cmd->argv);
	new_argv = extend_argv(cmd->argv, argc, value);
	if (!new_argv)
		return (-1);
	free(cmd->argv);
	cmd->argv = new_argv;
	return (0);
}
