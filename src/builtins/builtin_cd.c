/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 11:32:04 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/07 15:35:19 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char **args, t_env **env)
{
	char	*target;
	char	cwd[4096];
	char	*oldpwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("minishell: cd");
		return (1);
	}
	oldpwd = ft_strdup(cwd);
	if (!args[1])
	{
		target = ft_getenv(*env, "HOME");
		if (!target)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			free(oldpwd);
			return (1);
		}
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		target = ft_getenv(*env, "OLDPWD");
		if (!target)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			free(oldpwd);
			return (1);
		}
		ft_putendl_fd(target, 1);
	}
	else
		target = args[1];
	if (chdir(target) != 0)
	{
		perror("minishell: cd");
		free(oldpwd);
		return (1);
	}
	ft_setenv(env, "OLDPWD", oldpwd, 1);
	free(oldpwd);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("minishell: cd");
		return (1);
	}
	ft_setenv(env, "PWD", cwd, 1);
	return (0);
}
