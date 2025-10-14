/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 11:32:04 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/28 00:18:48 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_cd_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	if (count > 2)
		return (print_minishell_error("cd", NULL, ERR_TOO_MNY_ARGS, 1));
	return (last_status(1, 0));
}

static char	*get_cd_target(char **args, t_env **env)
{
	if (!args[1])
	{
		if (!ft_getenv(*env, "HOME"))
			return (print_minishell_error("cd", NULL, ERR_H_NT_SET, 1), NULL);
		return (ft_getenv(*env, "HOME"));
	}
	if (ft_strcmp(args[1], "-") == 0)
	{
		if (!ft_getenv(*env, "OLDPWD"))
			return (print_minishell_error("cd", NULL, ERR_O_NT_SET, 1), NULL);
		ft_putendl_fd(ft_getenv(*env, "OLDPWD"), 1);
		return (ft_getenv(*env, "OLDPWD"));
	}
	return (args[1]);
}

int	builtin_cd(char **args, t_env **env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;
	char	*target;

	if (check_cd_args(args))
		return (last_status(1, 1));
	if (!getcwd(cwd, sizeof(cwd)))
		return (print_minishell_error("cd", NULL, ERR_RET_CUR_DIR, 1));
	oldpwd = ft_strdup(cwd);
	target = get_cd_target(args, env);
	if (!target)
		return (free(oldpwd), EXIT_SUCCESS);
	if (chdir(target) != 0)
		return (print_minishell_error("cd", target, ERR_DIR, 1),
			free(oldpwd), 1);
	ft_setenv(env, "OLDPWD", oldpwd, 1);
	free(oldpwd);
	if (!getcwd(cwd, sizeof(cwd)))
		return (print_minishell_error("cd", NULL, ERR_RET_CUR_DIR, 1));
	ft_setenv(env, "PWD", cwd, 1);
	return (last_status(1, 0));
}
