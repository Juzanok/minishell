/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:02:00 by hrings            #+#    #+#             */
/*   Updated: 2022/07/02 08:51:06 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	index_add(char *line, int index, int i)
{
	if (line[index + i] == '\"')
		i += next_d_quote(line, index, i);
	else if (line[index + i] == '\'')
		i += next_s_quote(line, index, i);
	else
		i++;
	return (i);
}

int	next_d_quote(char *line, int index, int i)
{
	int	result;

	result = 1;
	while (line[index + i + result] != '\"')
		result++;
	result++;
	return (result);
}

int	next_s_quote(char *line, int index, int i)
{
	int	result;

	result = 1;
	while (line[index + i + result] != '\'')
		result++;
	result++;
	return (result);
}
