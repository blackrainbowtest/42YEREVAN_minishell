/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 23:07:48 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/23 19:52:08 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_redir	t_redir;
typedef struct s_env	t_env;
typedef struct s_token	t_token;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redir;
	struct s_cmd	*next;
}				t_cmd;

// ===== parser_line.c =====
t_cmd	*parse_line(const char *line, t_env *env);

// ===== parser_tokens.c =====
t_cmd	*parse_tokens(t_token *tokens);
void	free_cmds(t_cmd *cmds);
#endif // PARSER_H
