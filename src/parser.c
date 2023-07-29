/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:29:29 by hrings            #+#    #+#             */
/*   Updated: 2022/07/27 12:37:59 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	find_end_index(char *line, int index);

void	parser(t_minishell *param, char *line)
{
	int	index;
	int	start_index;
	int	end_index;

	index = 0;
	index += skip_whitespace(line, index);
	while (line[index] != '\0')
	{
		index += skip_whitespace(line, index);
		start_index = index;
		index = find_end_index(line, index);
		end_index = index;
		if (start_index == end_index)
		{
			error_parser(param, PARSEPIPE, line[index]);
			break ;
		}
		list_push(param, ft_substr(line, start_index, \
					end_index - start_index));
		if (line[index] != '\0')
			index++;
	}
	if (param->input)
		param->num_com = ft_input_size(param->input);
}

static int	find_end_index(char *line, int index)
{
	while (line[index] != '|' && line[index] != '\0')
	{
		if (line[index] == '\"')
		{
			index++;
			while (line[index] != '\"')
				index++;
			index++;
		}
		else if (line[index] == '\'')
		{
			index++;
			while (line[index] != '\'')
				index++;
			index++;
		}
		else
			index++;
	}
	return (index);
}

void	print_list(t_minishell *param)
{
	t_input	*current;

	current = param->input;
	while (current)
	{
		printf("%s\n", current->line);
		current = current->next;
	}
}
