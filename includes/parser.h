/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 23:07:48 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/24 00:21:01 by aramarak         ###   ########.fr       */
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

// ===== expand_tokens.c =====
void	expand_tokens(t_token *tokens, t_env *env);
char	*expand_string(const char *str, t_env *env);

// ===== expand_utils.c =====
void	expand_var_token(t_token *tok, t_env *env);
void	expand_word_token(t_token *tok, t_env *env);
void	expand_dquote_token(t_token *tok, t_env *env);
void	append_char(char **result, char c);
void	append_str(char **result, const char *s);

#endif // PARSER_H
