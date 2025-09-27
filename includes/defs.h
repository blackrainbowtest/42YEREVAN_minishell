/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:37:27 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/27 18:36:45 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# define DEBUG 1

# define PWD_CRWD "minishell: pwd: cannot retrieve working directory\n"
# define EXP_AERR "minishell: export: %s: allocation error\n"

# define ERR_SYN_EOF "minishell: syntax error: unexpected EOF while\
looking for matching `%c`\n"
# define EXP_INV "minishell: export: `%s': not a valid identifier\n"

#endif // DEFS_H