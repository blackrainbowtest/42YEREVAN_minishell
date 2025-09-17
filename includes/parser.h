/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 23:07:48 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/14 00:20:49 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_redir	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redir;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}	t_token;

// ===== parser_pipe =====
t_cmd	*parse_pipeline(const char *line);
void	print_cmds(t_cmd *cmds);

// ===== parser_utils =====
void	free_cmds(t_cmd *cmds);
void	free_redirs(t_redir *redir);
char	**split_pipes(const char *line);

// ===== parser.c =====
char	**parse_input(const char *line);
void	free_argv(char **argv);
int		is_redirection(const char *s);

// ===== tokenizer.c =====
char	**tokenize(const char *line);

#endif // PARSER_H