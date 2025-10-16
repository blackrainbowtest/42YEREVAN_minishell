/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 23:07:48 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/16 20:07:43 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_redir		t_redir;
typedef struct s_env		t_env;
typedef struct s_token		t_token;
typedef enum e_toktype		t_toktype;
typedef enum e_redir_type	t_redir_type;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redir;
	struct s_cmd	*next;
}				t_cmd;

// ===== parser_line.c =====
t_cmd	*parse_line(const char *line, t_env *env, t_env **locals);

// ===== expand_tokens.c =====
void	expand_tokens(t_token *tokens, t_env *env, t_env *locals);
char	*expand_local_env_var(const char *str,
			size_t start, size_t end, t_env *locals);
char	*expand_env_var(const char *str, size_t start, size_t end,
			t_env *env);
char	*expand_status(size_t *i);

// ===== expand_tokens_utils.c =====
char	*expand_string(const char *str, t_env *env, t_env *locals);
char	*expand_dollar(const char *str,
			size_t *i, t_env *env, t_env *locals);

// ===== parse_tokens_utils.c =====
int		add_arg(t_cmd *cmd, const char *value);
int		ensure_current_cmd(t_cmd **cur, t_cmd **head);
int		handle_word_token(t_cmd *cur, t_token *tok,
			t_env **locals);
int		handle_redir_token(t_cmd *cur, t_token **tok, t_cmd *head);
int		handle_pipe_token(t_cmd **cur, t_cmd *head);

// ===== expand_utils.c =====
void	expand_var_token(t_token *tok, t_env *env, t_env *locals);
void	expand_word_token(t_token *tok, t_env *env, t_env *locals);
void	expand_dquote_token(t_token *tok, t_env *env, t_env *locals);
void	append_char(char **result, char c);
void	append_str(char **result, const char *s);

/* ===== parse_utils.c ===== */
int		add_redir(t_cmd *cmd, t_redir_type type, const char *file);
t_cmd	*new_cmd(void);

void	free_cmds(t_cmd *cmds);
t_cmd	*parse_tokens(t_token *tokens, t_env **locals);

/* ===== parse_tokens_process.c ===== */
int		process_token(t_cmd **cur, t_cmd **head,
			t_token **tok, t_env **locals);

#endif // PARSER_H
