/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:36:13 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/16 20:10:26 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_arg(t_cmd *cmd, const char *value)
{
	int		argc;
	char	**new_argv;

	argc = 0;
	if (cmd->argv)
	{
		while (cmd->argv[argc])
			argc++;
	}
	new_argv = malloc(sizeof(char *) * (argc + 2));
	if (!new_argv)
		return (-1);
	for (int i = 0; i < argc; i++)
		new_argv[i] = cmd->argv[i];
	new_argv[argc] = ft_strdup(value ? value : "");
	if (!new_argv[argc])
	{
		free(new_argv);
		return (-1);
	}
	new_argv[argc + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
	return (0);
}


static int	ft_arrlen(char **arr)
{
	int	i = 0;

	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

/** TODO: fix segfault here if after $ nothing */
/** TODO: need to fix art_index and maybe delete this */
int	handle_word_token(t_cmd *cur, t_token *tok,
	t_env **locals)
{
	char	*old;
	int		last_idx;

	if (!tok->value)
		tok->value = ft_strdup("");
	if (is_assignment_token(tok->value))
	{
		if (!cur->argv || ft_strcmp(cur->argv[0], "export") != 0)
			return (handle_assignment(locals, tok->value), 1);
	}
	last_idx = ft_arrlen(cur->argv) - 1;
	if (tok->space_before == 0 && last_idx >= 0)
	{
		old = cur->argv[last_idx];
		cur->argv[last_idx] = ft_strjoin(old, tok->value);
		free(old);
	}
	else
	{
		if (tok->value)
		{
			if (add_arg(cur, tok->value) < 0)
				return (-1);
		}
		else
		{
			if (add_arg(cur, "") < 0)
				return (-1);
		}
	}
	return (0);
}

static t_redir_type	token_to_redir_type(t_toktype type)
{
	if (type == T_REDIR_IN)
		return (R_IN);
	if (type == T_REDIR_OUT)
		return (R_OUT);
	if (type == T_REDIR_APPEND)
		return (R_APPEND);
	if (type == T_HEREDOC)
		return (R_HEREDOC);
	return (R_NONE);
}

int	handle_redir_token(t_cmd *cur, t_token **tok, t_cmd *head)
{
	t_redir_type	rtype;

	if (!(*tok)->next || (*tok)->next->type != T_WORD)
	{
		fprintf(stderr, "minishell: syntax error near redirection\n");
		free_cmds(head);
		return (-1);
	}
	rtype = token_to_redir_type((*tok)->type);
	if (rtype == R_NONE)
	{
		fprintf(stderr, "minishell: internal error: unknown redir type\n");
		free_cmds(head);
		return (-1);
	}
	if (add_redir(cur, rtype, (*tok)->next->value) < 0)
	{
		free_cmds(head);
		return (-1);
	}
	*tok = (*tok)->next;
	return (1);
}


int	handle_pipe_token(t_cmd **cur, t_cmd *head)
{
	(*cur)->next = new_cmd();
	if (!(*cur)->next)
	{
		free_cmds(head);
		return (-1);
	}
	*cur = (*cur)->next;
	return (0);
}
