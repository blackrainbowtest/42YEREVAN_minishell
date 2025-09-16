/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:40:33 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/14 16:59:06 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_trunc(char *file)
{
	return open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

int	open_append(char *file)
{
	return open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

int	open_read(char *file)
{
	return open(file, O_RDONLY);
}

/**
 * TODO: later we will make a full heredoc
 * for now we can return -1 (not implemented)
 */
int	open_heredoc(char *limiter)
{
	(void)limiter;
    return (-1);
}
