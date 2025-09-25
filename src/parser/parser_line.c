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
t_cmd	*parse_line(const char *line, t_env *env, t_env **locals)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = tokenize(line);
	if (!tokens)
		return (NULL);
	expand_tokens(tokens, env);
	cmds = parse_tokens(tokens, locals);
	if (DEBUGING)
		debug_print_cmds(cmds);
	free_tokens(tokens);
	return (cmds);
}
