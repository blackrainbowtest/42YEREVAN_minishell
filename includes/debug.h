/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debuh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:37:27 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/07 22:38:16 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# define DEBUGING 1

typedef struct s_cmd	t_cmd;
typedef struct s_token	t_token;

void	debug_print_cmds(t_cmd *cmds);
void	print_tokens(t_token *tokens);

#endif