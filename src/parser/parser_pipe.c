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

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->argv)
			free_argv(cmds->argv);
		if (cmds->infile)
			free(cmds->infile);
		if (cmds->outfile)
			free(cmds->outfile);
		free(cmds);
		cmds = tmp;
	}
}

static char	**split_pipes(const char *line)
{
	char	**parts;

	parts = ft_split(line, '|');
	return (parts);
}

t_cmd	*parse_pipeline(const char *line)
{
	char	**parts;
	t_cmd	*head;
	t_cmd	*cur;
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
		t_cmd *node = malloc(sizeof(t_cmd));
		if (!node)
		{
			free_cmds(head);
			free_argv(parts);
			return (NULL);
		}
		node->argv = parse_input(parts[i]);
		node->infile = NULL;
		node->outfile = NULL;
		node->append = 0;
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
	int	i;

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
		if (cmds->infile)
			printf("infile: %s\n", cmds->infile);
		if (cmds->outfile)
			printf("outfile: %s (append=%d)\n", cmds->outfile, cmds->append);
		cmds = cmds->next;
	}
}
