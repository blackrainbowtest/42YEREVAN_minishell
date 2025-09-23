/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:45:59 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/05 18:45:59 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*redir_type_to_str(t_redir_type type)
{
	if (type == R_IN)
		return ("R_IN (<)");
	else if (type == R_OUT)
		return ("R_OUT (>)");
	else if (type == R_APPEND)
		return ("R_APPEND (>>)");
	else if (type == R_HEREDOC)
		return ("R_HEREDOC (<<)");
	return ("UNKNOWN");
}

const char	*toktype_to_str(t_toktype type)
{
	if (type == T_WORD)
		return ("T_WORD");
	else if (type == T_PIPE)
		return ("T_PIPE");
	else if (type == T_VAR)
		return ("T_VAR");
	else if (type == T_REDIR_IN)
		return ("T_REDIR_IN");
	else if (type == T_REDIR_OUT)
		return ("T_REDIR_OUT");
	else if (type == T_REDIR_APPEND)
		return ("T_REDIR_APPEND");
	else if (type == T_HEREDOC)
		return ("T_HEREDOC");
	return ("UNKNOWN");
}

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	printf("=== TOKENS ===\n");
	while (tokens)
	{
		printf("[%d] type=%s, value='%s'\n",
			i, toktype_to_str(tokens->type), tokens->value);
		tokens = tokens->next;
		i++;
	}
	printf("==============\n");
}

void	debug_print_cmds(t_cmd *cmds)
{
	int		i;
	t_redir	*r;

	while (cmds)
	{
		printf("\033[32m=== Command ===\033[0m\n");
		if (cmds->argv)
		{
			i = -1;
			while (cmds->argv[++i])
				printf("  argv[%d]: %s\n", i, cmds->argv[i]);
		}
		r = cmds->redir;
		while (r)
		{
			printf("  redir: type=%s, file=%s\n",
				redir_type_to_str(r->type), r->file);
			r = r->next;
		}
		cmds = cmds->next;
		if (cmds)
			printf("--- PIPE ---\n");
		printf("\033[32m=== END Command ===\033[0m\n");
	}
}

void	debug_print_cmd_args(t_cmd *cmds)
{
	t_cmd	*cmd;
	int		i;

	cmd = cmds;
	while (cmd)
	{
		printf("=== Command ===\n");
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			printf("  argv[%d]: %s\n", i, cmd->argv[i]);
			i++;
		}
		cmd = cmd->next;
	}
}
