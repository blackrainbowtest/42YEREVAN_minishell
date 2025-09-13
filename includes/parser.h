/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 23:07:48 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/13 14:32:44 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	int				append;
	struct s_cmd	*next;
}				t_cmd;

// ===== parser =====
// Простая версия: разбивка по пробелам/табам (без кавычек пока)
char	**parse_input(const char *line);
void	free_argv(char **argv);

#endif // PARSER_H