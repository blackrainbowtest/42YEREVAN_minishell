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
	new_argv[argc] = ft_strdup(value);
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



/** TODO: fix segfault here if after $ nothing */
int	handle_word_token(t_cmd *cur, t_token *tok,
	t_env **locals, int *arg_index)
{
	char	*old;

	if (!tok->value)
		return (0);

	if (is_assignment_token(tok->value))
	{
		if (!cur->argv || ft_strcmp(cur->argv[0], "export") != 0)
			return (handle_assignment(locals, tok->value), 1);
	}

	if (tok->space_before == 0 && cur->argv && *arg_index >= 0)
	{
		old = cur->argv[*arg_index];
		cur->argv[*arg_index] = ft_strjoin(old, tok->value);
		free(old);
	}
	else
	{
		if (add_arg(cur, tok->value) < 0)
			return (-1);
		(*arg_index)++;
	}
	return (0);
}

int	handle_redir_token(t_cmd *cur, t_token *tok, t_cmd *head)
{
	if (!tok->next || tok->next->type != T_WORD)
	{
		fprintf(stderr, "minishell: syntax error near redirection\n");
		free_cmds(head);
		return (-1);
	}
	if (add_redir(cur, tok->type, tok->next->value) < 0)
	{
		free_cmds(head);
		return (-1);
	}
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
