/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:36:13 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/16 20:10:26 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees a linked list of tokens.
 *
 * Iterates through a linked list of `t_token` structures, freeing the memory
 * allocated for each token's `value` string and the token itself. After this
 * function is called, the entire list is deallocated and no longer accessible.
 *
 * @param tokens Pointer to the first token in the linked list. Can be NULL,
 *        in which case the function does nothing.
 *
 * @return This function does not return a value.
 *
 * @note After calling this function, all pointers to tokens or their values
 *       become invalid.
 * @warning Do not call this function on a list that has already been freed,
 *          as it will cause undefined behavior.
 * @bug None known.
 * @todo None.
 */
static void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

/**
 * @brief Parses a command line string into a list of command structures.
 *
 * This function takes a raw input line, tokenizes it into a linked list of
 * `t_token` elements, and then converts those tokens into a higher-level
 * representation (`t_cmd` structures). After parsing, the temporary token
 * list is freed, and only the command structures remain. This is the main
 * entry point for processing user input into an internal format suitable
 * for execution.
 *
 * @param line The raw command line string to parse. Must not be NULL.
 *
 * @return A pointer to the head of a `t_cmd` structure list representing
 *         the parsed commands. Returns NULL if tokenization fails, parsing
 *         fails, or if memory allocation errors occur.
 *
 * @note The returned `t_cmd` list must be freed by the caller using the
 *       appropriate cleanup function.
 * @warning If `line` contains syntax errors, `parse_tokens` may return NULL.
 * @bug None known.
 * @todo Implement more advanced error handling for malformed input.
 */
t_cmd	*parse_line(const char *line)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = tokenize(line);
	if (!tokens)
		return (NULL);
	cmds = parse_tokens(tokens);
	free_tokens(tokens);
	return cmds;
}
