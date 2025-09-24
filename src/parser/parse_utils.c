/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 01:46:57 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/25 01:55:06 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int merge_token(t_cmd *cmd, t_token *tok, int *arg_index)
{
	if (!cmd->argv)
	{
		cmd->argv = malloc(sizeof(char *) * 2);
		if (!cmd->argv)
			return (-1);
		cmd->argv[0] = ft_strdup(tok->value);
		if (!cmd->argv[0])
			return (-1);
		cmd->argv[1] = NULL;
		*arg_index = 0;
	}
	else if (tok->space_before == 0 && *arg_index >= 0)
	{
		char *old = cmd->argv[*arg_index];
		cmd->argv[*arg_index] = ft_strjoin(old, tok->value);
		free(old);
		if (!cmd->argv[*arg_index])
			return (-1);
	}
	else
	{
		int i = 0;
		while (cmd->argv[i])
			i++;
		char **new_argv = malloc(sizeof(char *) * (i + 2));
		if (!new_argv)
			return (-1);
		for (int j = 0; j < i; j++)
			new_argv[j] = cmd->argv[j];
		new_argv[i] = ft_strdup(tok->value);
		if (!new_argv[i])
		{
			free(new_argv);
			return (-1);
		}
		new_argv[i + 1] = NULL;
		free(cmd->argv);
		cmd->argv = new_argv;
		*arg_index = i;
	}
	return (0);
}

t_cmd *new_cmd(void)
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return NULL;
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return cmd;
}

int add_redir(t_cmd *cmd, t_toktype type, const char *file)
{
	t_redir *new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (-1);
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
	if (!new_redir->file)
	{
		free(new_redir);
		return (-1);
	}
	new_redir->next = NULL;

	if (!cmd->redir)
		cmd->redir = new_redir;
	else
	{
		t_redir *tmp = cmd->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redir;
	}
	return 0;
}
