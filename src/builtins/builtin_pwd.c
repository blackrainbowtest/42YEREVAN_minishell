/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 19:54:39 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/07 22:39:03 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_env *env)
{
	char	cwd[4096];
	char	*pwd;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		pwd = ft_getenv(env, "PWD");
		if (pwd)
		{
			ft_putstr_fd(pwd, 1);
			ft_putstr_fd("\n", 1);
		}
		else
		{
			ft_putstr_fd(PWD_CRWD, 2);
			return (1);
		}
	}
	return (0);
}
