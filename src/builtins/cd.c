/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 11:32:04 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/27 19:00:10 by aramarak         ###   ########.fr       */
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
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		last_status(1, 1);
		return (1);
	}
	last_status(1, 0);
	return (0);
}

static char	*get_cd_target(char **args, t_env **env)
{
	if (!args[1])
	{
		if (!ft_getenv(*env, "HOME"))
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
		return (ft_getenv(*env, "HOME"));
	}
	if (ft_strcmp(args[1], "-") == 0)
	{
		if (!ft_getenv(*env, "OLDPWD"))
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (NULL);
		}
		ft_putendl_fd(ft_getenv(*env, "OLDPWD"), 1);
		return (ft_getenv(*env, "OLDPWD"));
	}
	return (args[1]);
}

int	builtin_cd(char **args, t_env **env)
{
	char	cwd[4096];
	char	*oldpwd;
	char	*target;

	if (check_cd_args(args))
		return (1);
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("minishell: cd"), 1);
	oldpwd = ft_strdup(cwd);
	target = get_cd_target(args, env);
	if (!target)
		return (free(oldpwd), 1);
	if (chdir(target) != 0)
		return (perror("minishell: cd"), free(oldpwd), 1);
	ft_setenv(env, "OLDPWD", oldpwd, 1);
	free(oldpwd);
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("minishell: cd"), 1);
	ft_setenv(env, "PWD", cwd, 1);
	return (0);
}
