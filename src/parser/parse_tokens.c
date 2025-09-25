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

t_cmd	*parse_tokens(t_token *tokens, t_env **locals)
{
	t_cmd	*head;
	t_cmd	*cur;
	t_token	*tok;
	int arg_index = -1;

	head = NULL;
	cur = NULL;
	tok = tokens;
	(void)locals;
	while (tok)
	{
		if (!cur)
		{
			cur = new_cmd();
			if (!cur)
				return (free_cmds(head), NULL);
			if (!head)
				head = cur;
		}
		if (tok->type == T_WORD || tok->type == T_VAR
			|| tok->type == T_DQUOTE || tok->type == T_SQUOTE)
		{
			if (is_assignment_token(tok->value))
			{
				handle_assignment(locals, tok->value);
				tok = tok->next;
				continue ;
			}
			if (tok->space_before == 0 && cur->argv && arg_index >= 0)
			{
				char *old = cur->argv[arg_index];
				cur->argv[arg_index] = ft_strjoin(old, tok->value);
				free(old);
			}
			else
			{
				if (add_arg(cur, tok->value) < 0)
				{
					free_cmds(head);
					return (NULL);
				}
				arg_index++;
			}
		}
		else if (tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT
			|| tok->type == T_REDIR_APPEND || tok->type == T_HEREDOC)
		{
			if (!tok->next || tok->next->type != T_WORD)
			{
				fprintf(stderr, "minishell: syntax error near redirection\n");
				return (free_cmds(head), NULL);
			}
			if (add_redir(cur, tok->type, tok->next->value) < 0)
				return (free_cmds(head), NULL);
			tok = tok->next;
		}
		else if (tok->type == T_PIPE)
		{
			cur->next = new_cmd();
			if (!cur->next)
				return (free_cmds(head), NULL);
			cur = cur->next;
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
