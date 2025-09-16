/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:36:13 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/14 00:20:40 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	*create_redir_node(const char *token, const char *file)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->file = ft_strdup(file);
	if (!node->file)
		return (free(node), NULL);
	if (ft_strcmp(token, "<") == 0)
		node->type = 0;
	else if (ft_strcmp(token, ">") == 0)
		node->type = 1;
	else if (ft_strcmp(token, ">>") == 0)
		node->type = 2;
	else
		node->type = 3;
	node->next = NULL;
	return (node);
}

static void	remove_redir_from_argv(char **argv, int i)
{
	int	j;

	free(argv[i]);
	free(argv[i + 1]);
	j = i;
	while (argv[j + 2])
	{
		argv[j] = argv[j + 2];
		j++;
	}
	argv[j] = NULL;
	argv[j + 1] = NULL;
}

static t_redir	*parse_redirs(char **argv)
{
	t_redir	*head;
	t_redir	*cur;
	t_redir	*node;
	int		i;

	head = NULL;
	cur = NULL;
	i = 0;
	while (argv && argv[i])
	{
		if (is_redirection(argv[i]))
		{
			if (!argv[i + 1])
				return (free_redirs(head), NULL);
			node = create_redir_node(argv[i], argv[i + 1]);
			if (!node)
				return (free_redirs(head), NULL);
			if (!head)
				head = node;
			else
				cur->next = node;
			cur = node;
			remove_redir_from_argv(argv, i);
			continue ;
		}
		i++;
	}
	return (head);
}

t_cmd	*parse_pipeline(const char *line)
{
	char	**parts;
	t_cmd	*head;
	t_cmd	*cur;
	t_cmd	*node;
	int		i;

	if (!line)
		return (NULL);
	parts = split_pipes(line);
	if (!parts)
		return (NULL);
	head = NULL;
	cur = NULL;
	i = 0;
	while (parts[i])
	{
		node = malloc(sizeof(t_cmd));
		if (!node)
			return (free_cmds(head), free_argv(parts), NULL);
		node->argv = parse_input(parts[i]);
		node->redir = parse_redirs(node->argv);
		node->next = NULL;
		if (!head)
			head = node;
		else
			cur->next = node;
		cur = node;
		i++;
	}
	free_argv(parts);
	return (head);
}

void	print_cmds(t_cmd *cmds)
{
	int		i;
	t_redir	*r;

	while (cmds)
	{
		printf("=== Command ===\n");
		if (cmds->argv)
		{
			i = 0;
			while (cmds->argv[i])
			{
				printf("argv[%d]: %s\n", i, cmds->argv[i]);
				i++;
			}
		}
		r = cmds->redir;
		while (r)
		{
			printf("redir: type=%d, file=%s\n", r->type, r->file);
			r = r->next;
		}
		cmds = cmds->next;
	}
}
