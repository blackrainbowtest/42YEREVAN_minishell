/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:23:31 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/25 13:01:32 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_storage(t_env *new_env, int mode)
{
	static t_env	*env_ptr;

	if (mode == SET)
		env_ptr = new_env;
	else if (mode == FREE)
	{
		free_env(env_ptr);
		env_ptr = NULL;
	}
	return (env_ptr);
}

t_env	*locals_storage(t_env *new_locals, int mode)
{
	static t_env	*locals_ptr;

	if (mode == SET)
		locals_ptr = new_locals;
	else if (mode == FREE)
	{
		free_locals(locals_ptr);
		locals_ptr = NULL;
	}
	return (locals_ptr);
}
