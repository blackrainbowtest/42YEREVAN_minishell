/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:37:27 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/18 22:47:14 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# define DEBUG 1
# define GET 0
# define SET 1

# define PWD_CRWD "minishell: pwd: cannot retrieve working directory\n"
# define EXP_AERR "minishell: export: %s: allocation error\n"

# define ERR_SYN_EOF "minishell: syntax error: unexpected EOF while\
looking for matching `%c`\n"
# define EXP_INV "minishell: export: `%s': not a valid identifier\n"

/* ===== export ===== */
# define ERR_MEM_ALLOC "Memory allocation error"
# define ERR_NT_VAL_INP "not a valid identifier"
# define ERR_MEM_AL "cannot allocate memory"
# define ERR_ALLOC "allocation error"

/* ===== cd =====*/
# define ERR_TOO_MNY_ARGS "too many arguments"
# define ERR_H_NT_SET "HOME not set"
# define ERR_O_NT_SET "OLDPWD not set"
# define ERR_RET_CUR_DIR "error retrieving current directory"
# define ERR_DIR "No such file or directory"
# define ERR_IS_DIR "Is a directory"
# define ERR_PERM "Permission denied"

/* ===== exit =====*/
# define ERR_NUMERIC "numeric argument required"

# define MIN_OUT "minishell: syntax error near unexpected token 'newline'"
# define MIN_UNKNOWN "minishell: internal error: unknown redir type"
#endif // DEFS_H