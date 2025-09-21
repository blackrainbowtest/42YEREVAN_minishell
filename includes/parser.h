/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 23:07:48 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/20 20:51:47 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_redir	t_redir;
typedef struct s_env	t_env;

typedef enum e_toktype
{
	T_WORD,
	T_PIPE,
	T_VAR,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
}			t_toktype;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redir;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_token
{
	char			*value;
	t_toktype		type;
	struct s_token	*next;
}				t_token;

// ===== parser_line.c =====
t_cmd	*parse_line(const char *line, t_env *env);

// ===== tokenizer.c =====
t_token	*tokenize(const char *line);
void	free_tokens(t_token *lst);

// ===== parser_tokens.c =====
t_cmd	*parse_tokens(t_token *tokens);
void	free_cmds(t_cmd *cmds);
#endif // PARSER_H
