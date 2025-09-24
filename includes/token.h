/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 23:07:48 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/20 20:51:47 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stddef.h>

typedef enum e_toktype
{
	T_WORD,
	T_PIPE,
	T_VAR,
	T_SQUOTE,
	T_DQUOTE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
}			t_toktype;

typedef struct s_token
{
	char			*value;
	t_toktype		type;
	int				space_before;
	struct s_token	*next;
}				t_token;

// ===== token_free.c =====
void		free_tokens(t_token *lst);

// ===== token_helper.c =====
int			skip_whitespace(const char *line, size_t *i);
void		add_quoted_token(t_token **head, const char *line,
			size_t *i, int had_space);
void		add_operator_token(t_token **head, const char *line, size_t *i,
			int had_space);
void		add_var_token(t_token **head, const char *line, size_t *i,
			int had_space);
void		add_word_token(t_token **head, const char *line, size_t *i,
			int had_space);

// ===== token_list.c =====
t_token		*new_token(const char *str, t_toktype type);
void		token_add_back(t_token **lst, t_token *new);
void		token_add_last(t_token **lst, char *str);
t_token		*get_last_token(t_token *lst);

// ===== token_quote.c =====
t_toktype	get_quote_type(char quote);
size_t		get_quoted_length(const char *line, size_t start, char quote);
t_token		*handle_unclosed_quote(char quote);
t_token		*read_quoted(const char *line, size_t *i);

// ===== tokenizer.c =====
t_token		*tokenize(const char *line);

#endif // TOKEN_H