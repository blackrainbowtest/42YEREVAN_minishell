/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:23:31 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/25 13:01:32 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_and_exit(int status)
{
	free_env(env_storage(NULL, GET));
	free_locals(locals_storage(NULL, GET));
	clear_history();
	exit(status);
}