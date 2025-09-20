/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:01:56 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/20 20:55:18 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;
/**
 * @brief Expands environment variables in the command arguments.
 * This function iterates over the list of commands and their
 * arguments, replacing any occurrences of environment
 * variables (e.g., $VAR) with their corresponding
 */
void	expand_tokens(t_token *tokens, t_env *env);

char	*expand_one(char *arg, t_env *env);
#endif