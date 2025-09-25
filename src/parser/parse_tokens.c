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

t_cmd *parse_tokens(t_token *tokens, t_env **locals)
{
    t_cmd *head = NULL;
    t_cmd *cur = NULL;
    t_token *tok = tokens;
    int arg_index = -1;

    while (tok)
    {
        if (!cur)
        {
            cur = new_cmd();
            if (!cur)
                return free_cmds(head), NULL;
            if (!head)
                head = cur;
        }

        if (tok->type == T_WORD || tok->type == T_VAR || tok->type == T_DQUOTE || tok->type == T_SQUOTE)
        {
			if (is_assignment_token(tok->value))
			{
				handle_assignment(locals, tok->value);
				tok = tok->next;
				continue;
			}
            if (merge_token(cur, tok, &arg_index) < 0)
                return free_cmds(head), NULL;
        }
        else if (tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT
              || tok->type == T_REDIR_APPEND || tok->type == T_HEREDOC)
        {
            arg_index = -1;
            if (!tok->next || tok->next->type != T_WORD)
            {
                fprintf(stderr, "minishell: syntax error near redirection\n");
                return free_cmds(head), NULL;
            }
            if (add_redir(cur, tok->type, tok->next->value) < 0)
                return free_cmds(head), NULL;
            tok = tok->next;
        }
        else if (tok->type == T_PIPE)
        {
            arg_index = -1;
            cur->next = new_cmd();
            if (!cur->next)
                return free_cmds(head), NULL;
            cur = cur->next;
        }
        else
        {
            arg_index = -1;
        }

        tok = tok->next;
    }
    return head;
}

void free_cmds(t_cmd *cmds)
{
    while (cmds)
    {
        t_cmd *tmp = cmds->next;

        if (cmds->argv)
        {
            for (int i = 0; cmds->argv[i]; i++)
                free(cmds->argv[i]);
            free(cmds->argv);
        }

        t_redir *r = cmds->redir;
        while (r)
        {
            t_redir *r_tmp = r->next;
            free(r->file);
            free(r);
            r = r_tmp;
        }

        free(cmds);
        cmds = tmp;
    }
}

// static int	add_arg(t_cmd *cmd, const char *value)
// {
// 	int		argc;
// 	char	**new_argv;

// 	argc = 0;
// 	if (cmd->argv)
// 	{
// 		while (cmd->argv[argc])
// 			argc++;
// 	}
// 	new_argv = malloc(sizeof(char *) * (argc + 2));
// 	if (!new_argv)
// 		return (-1);
// 	for (int i = 0; i < argc; i++)
// 		new_argv[i] = cmd->argv[i];
// 	new_argv[argc] = ft_strdup(value);
// 	if (!new_argv[argc])
// 	{
// 		free(new_argv);
// 		return (-1);
// 	}
// 	new_argv[argc + 1] = NULL;
// 	free(cmd->argv);
// 	cmd->argv = new_argv;
// 	return (0);
// }

// static int	add_redir(t_cmd *cmd, t_toktype type, const char *file)
// {
// 	t_redir	*new_redir;
// 	t_redir	*tmp;

// 	new_redir = malloc(sizeof(t_redir));
// 	if (!new_redir)
// 		return (-1);
// 	new_redir->type = type;
// 	new_redir->file = ft_strdup(file);
// 	new_redir->next = NULL;
// 	if (!new_redir->file)
// 	{
// 		free(new_redir);
// 		return (-1);
// 	}
// 	if (!cmd->redir)
// 		cmd->redir = new_redir;
// 	else
// 	{
// 		tmp = cmd->redir;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = new_redir;
// 	}
// 	return (0);
// }

// static t_cmd	*new_cmd(void)
// {
// 	t_cmd	*cmd;

// 	cmd = malloc(sizeof(t_cmd));
// 	if (!cmd)
// 		return (NULL);
// 	cmd->argv = NULL;
// 	cmd->redir = NULL;
// 	cmd->next = NULL;
// 	return (cmd);
// }

// t_cmd	*parse_tokens(t_token *tokens)
// {
// 	t_cmd	*head;
// 	t_cmd	*cur;
// 	t_token	*tok;

// 	head = NULL;
// 	cur = NULL;
// 	tok = tokens;
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
// 		if (tok->type == T_WORD || tok->type == T_VAR || tok->type == T_DQUOTE || tok->type == T_SQUOTE)
// 		{
// 			if (add_arg(cur, tok->value) < 0)
// 				return (free_cmds(head), NULL);
// 		}
// 		else if (tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT
// 			|| tok->type == T_REDIR_APPEND || tok->type == T_HEREDOC)
// 		{
// 			if (!tok->next || tok->next->type != T_WORD)
// 			{
// 				fprintf(stderr, "minishell: syntax error near redirection\n");
// 				return (free_cmds(head), NULL);
// 			}
// 			if (add_redir(cur, tok->type, tok->next->value) < 0)
// 				return (free_cmds(head), NULL);
// 			tok = tok->next;
// 		}
// 		else if (tok->type == T_PIPE)
// 		{
// 			cur->next = new_cmd();
// 			if (!cur->next)
// 				return (free_cmds(head), NULL);
// 			cur = cur->next;
// 		}
// 		tok = tok->next;
// 	}
// 	return (head);
// }

// void	free_cmds(t_cmd *cmds)
// {
// 	t_cmd	*tmp;
// 	t_redir	*r;
// 	t_redir	*r_tmp;

// 	while (cmds)
// 	{
// 		tmp = cmds->next;
// 		if (cmds->argv)
// 		{
// 			for (int i = 0; cmds->argv[i]; i++)
// 				free(cmds->argv[i]);
// 			free(cmds->argv);
// 		}
// 		r = cmds->redir;
// 		while (r)
// 		{
// 			r_tmp = r->next;
// 			free(r->file);
// 			free(r);
// 			r = r_tmp;
// 		}
// 		free(cmds);
// 		cmds = tmp;
// 	}
// }
