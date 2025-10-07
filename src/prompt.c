/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:23:23 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/01 00:57:38 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Reads a line of input from the user with a shell prompt.
 *
 * This function displays the prompt "minishell$ " and waits for the user
 * to enter a line. If the user enters a non-empty line, it is added to
 * the readline history. This function handles basic input only and
 * does not perform parsing or command execution.
 *
 * @return A pointer to the string entered by the user.
 *         Returns NULL if end-of-file (Ctrl+D) is reached or on input error.
 *
 * @note The returned string should be freed by the caller to avoid memory leaks.
 * @warning The function relies on the GNU readline library; make sure to link
 *          with `-lreadline` during compilation.
 */
char	*read_prompt(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
		return (NULL);
	return (line);
}
