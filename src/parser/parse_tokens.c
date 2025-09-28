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

// t_cmd   *parse_tokens(t_token *tokens, t_env **locals)
// {
// 	t_cmd *head = NULL;
// 	t_cmd *cur = NULL;
// 	t_token *tok = tokens;
// 	int arg_index = -1;

// 	while (tok)
// 	{
// 		if (!cur)
// 		{
// 			cur = new_cmd();
// 			if (!cur)
// 				return (free_cmds(head), NULL);
// 			if (!head)
// 				head = cur;
// 		}

// 		if (tok->type == T_WORD || tok->type == T_VAR
// 			|| tok->type == T_DQUOTE || tok->type == T_SQUOTE)
// 		{
// 			if (is_assignment_token(tok->value))
// 			{
// 				handle_assignment(locals, tok->value);
// 				tok = tok->next;
// 				continue ;
// 			}
// 			if (merge_token(cur, tok, &arg_index) < 0)
// 			{
// 				free_cmds(head);
// 				return (NULL);
// 			}
// 		}
// 		else if (tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT
// 			|| tok->type == T_REDIR_APPEND || tok->type == T_HEREDOC)
// 		{
// 			arg_index = -1;
// 			if (!tok->next || tok->next->type != T_WORD)
// 			{
// 				fprintf(stderr, "minishell: syntax error near redirection\n");
// 				return free_cmds(head), NULL;
// 			}
// 			if (add_redir(cur, tok->type, tok->next->value) < 0)
// 				return free_cmds(head), NULL;
// 			tok = tok->next;
// 		}
// 		else if (tok->type == T_PIPE)
// 		{
// 			arg_index = -1;
// 			cur->next = new_cmd();
// 			if (!cur->next)
// 				return free_cmds(head), NULL;
// 			cur = cur->next;
// 		}
// 		else
// 		{
// 			arg_index = -1;
// 		}

// 		tok = tok->next;
// 	}
// 	return (head);
// }

static int	add_arg(t_cmd *cmd, const char *value)
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

static int ensure_current_cmd(t_cmd **cur, t_cmd **head)
{
    if (!*cur)
    {
        *cur = new_cmd();
        if (!*cur)
            return (-1);
        if (!*head)
            *head = *cur;
    }
    return (0);
}

static int	handle_word_token(t_cmd *cur, t_token *tok, t_env **locals, int *arg_index)
{
	if (!tok->value)
		return (0);

	if (is_assignment_token(tok->value))
	{
		if (!cur->argv || ft_strcmp(cur->argv[0], "export") != 0)
		{
			handle_assignment(locals, tok->value);
			return (1);
		}
	}

	if (tok->space_before == 0 && cur->argv && *arg_index >= 0)
	{
		char *old = cur->argv[*arg_index];
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

static int	handle_redir_token(t_cmd *cur, t_token *tok, t_cmd *head)
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

static int	handle_pipe_token(t_cmd **cur, t_cmd *head)
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

t_cmd *parse_tokens(t_token *tokens, t_env **locals)
{
	t_cmd *head = NULL;
	t_cmd *cur = NULL;
	t_token *tok = tokens;
	int arg_index = -1;

	while (tok)
	{
		// fprintf(stderr, "[parse_tokens] tok type=%d, value='%s', space_before=%d\n",
		// 	tok->type, tok->value ? tok->value : "(null)", tok->space_before);

		if (ensure_current_cmd(&cur, &head) < 0)
			return (NULL);

		if (tok->type == T_WORD || tok->type == T_VAR
			|| tok->type == T_DQUOTE || tok->type == T_SQUOTE)
		{
			int res = handle_word_token(cur, tok, locals, &arg_index);
			if (res < 0)
				return (NULL);
			if (res == 1) { tok = tok->next; continue; } // assignment skip
		}
		else if (tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT
			|| tok->type == T_REDIR_APPEND || tok->type == T_HEREDOC)
		{
			int res = handle_redir_token(cur, tok, head);
			if (res < 0)
				return (NULL);
			if (res == 1) { tok = tok->next; } // пропускаем filename
		}
		else if (tok->type == T_PIPE)
		{
			if (handle_pipe_token(&cur, head) < 0)
				return (NULL);
		}
		tok = tok->next;
	}
	return (head);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	t_redir	*r;
	t_redir	*r_tmp;
	int		i;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->argv)
		{
			i = 0;
			while (cmds->argv[i])
				free(cmds->argv[i++]);
			free(cmds->argv);
		}
		r = cmds->redir;
		while (r)
		{
			r_tmp = r->next;
			free(r->file);
			free(r);
			r = r_tmp;
		}
		free(cmds);
		cmds = tmp;
	}
}
