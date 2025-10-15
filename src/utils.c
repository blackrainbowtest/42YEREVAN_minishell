/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:33:48 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/04 10:06:36 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exec_path(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (print_minishell_error(NULL, path, ERR_DIR, 127));
	if (S_ISDIR(st.st_mode))
		return (print_minishell_error(NULL, path, ERR_IS_DIR, 126));
	if (access(path, X_OK) != 0)
		return (print_minishell_error(NULL, path, ERR_PERM, 126));
	return (0);
}
