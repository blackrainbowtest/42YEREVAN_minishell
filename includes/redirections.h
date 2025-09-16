/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:49:26 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/14 12:49:43 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "minishell.h"

// ===== t_redir structure =====
/**
 * @struct s_redir
 * @brief Structure to represent a redirection.
 * 
 * @arg file The file associated with the redirection.
 * @arg type The type of redirection (e.g., input, output, append, heredoc).
 * @arg next Pointer to the next redirection in the linked list.
 */
typedef struct s_redir
{
	char			*file;
	int				type;
	struct s_redir	*next;
}				t_redir;

// ===== apply_redirections.c =====
int		apply_redirections(t_cmd *cmd);

// ===== open_files.c =====
int		open_trunc(char *file);
int		open_append(char *file);
int		open_read(char *file);
int		open_heredoc(char *limiter);

// ===== utils_redir.c =====
int		is_input_redir(t_redir *r);
int		is_output_redir(t_redir *r);

#endif