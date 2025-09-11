/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:23:23 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/11 19:55:26 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * char *read_prompt(void);
 * (печатает "minishell$ " и ждёт ввод через readline())
 */

char	*read_prompt(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
		return (NULL);
	if (*line)
		add_history(line);
	return (line);
}
