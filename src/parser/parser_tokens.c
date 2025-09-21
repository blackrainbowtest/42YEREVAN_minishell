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
/**
 * @brief Adds a new argument string to a command structure.
 *
 * This function appends a new argument (`value`) to the `argv` array of the
 * given `t_cmd` structure. It reallocates the argument vector with enough
 * space for the new string and a NULL terminator. The old `argv` is freed,
 * and the updated pointer is stored back in the command structure.
 *
 * @param cmd Pointer to the command structure (`t_cmd`) whose argument list
 *        will be extended. Must not be NULL.
 * @param value The string to add as a new argument. Must not be NULL.
 *
 * @return Returns 0 on success. Returns -1 if memory allocation fails
 *         either when allocating the new array or when duplicating `value`.
 *
 * @note The function uses `ft_strdup` to copy `value`. The caller may safely
 *       free or modify the original `value` after calling.
 * @warning On allocation failure, the old `argv` remains unchanged, but the
 *          new array is freed to avoid memory leaks. However, if `ft_strdup`
 *          fails, previously copied pointers remain in the old array.
 * @bug Currently does not free already-copied arguments if `ft_strdup` fails,
 *      which may lead to a memory leak.
 * @todo Improve error handling to free partially allocated arrays if `ft_strdup`
 *       fails.
 */

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

// Добавляет редирект к команде
static int	add_redir(t_cmd *cmd, t_toktype type, const char *file)
{
	t_redir	*new_redir;
	t_redir	*tmp;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (-1);
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
	new_redir->next = NULL;
	if (!new_redir->file)
	{
		free(new_redir);
		return (-1);
	}
	if (!cmd->redir)
		cmd->redir = new_redir;
	else
	{
		tmp = cmd->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redir;
	}
	return (0);
}

static t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

// Основная функция парсинга токенов
t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*cur;
	t_token	*tok;

	head = NULL;
	cur = NULL;
	tok = tokens;
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
		if (tok->type == T_WORD || tok->type == T_VAR)
		{
			if (add_arg(cur, tok->value) < 0)
				return (free_cmds(head), NULL);
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

// Очистка списка команд
void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	t_redir	*r;
	t_redir	*r_tmp;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->argv)
		{
			for (int i = 0; cmds->argv[i]; i++)
				free(cmds->argv[i]);
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

