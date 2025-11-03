/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:38:56 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/03 19:38:56 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_invalid_key(char *arg)
{
	return (ft_strcmp(arg, "_") == 0 || ft_strncmp(arg, "_=", 2) == 0);
}

static int	handle_invalid_identifier(char *arg)
{
	print_minishell_error("export", arg, ERR_NT_VAL_INP, 1);
	return (1);
}

static int	export_arg(char *arg, t_env **env)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
		export_update_env(arg, env, eq, NULL);
	else if (ft_setenv(env, arg, "", 0) != 0)
		return (print_minishell_error("export", arg, ERR_MEM_AL, 1));
	return (0);
}

int	export_with_arguments(char **argv, t_env **env)
{
	int	status;
	int	i;

	status = 0;
	i = 1;
	while (argv[i])
	{
		if (skip_invalid_key(argv[i]))
			status = 1;
		else if (!is_valid_identifier(argv[i]))
			status = handle_invalid_identifier(argv[i]);
		else
			status |= export_arg(argv[i], env);
		i++;
	}
	last_status(1, status);
	return (status);
}
