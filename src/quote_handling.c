/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 08:18:17 by hrings            #+#    #+#             */
/*   Updated: 2022/07/27 10:09:04 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	add_till_next_d_qoute(char *line, char *result, t_index	*index);
static void	add_till_next_s_qoute(char *line, char *result, t_index	*index);

void	quote_handling(t_com *com)
{
	int		index;
	char	*result;

	index = 0;
	while (com->arg[index])
	{
		result = remove_quote(com->arg[index]);
		free(com->arg[index]);
		com->arg[index] = result;
		index++;
	}
	com->arg[index] = NULL;
}

char	*remove_quote(char *line)
{
	char	*result;
	t_index	*index;

	result = (char *)malloc(sizeof(char) * ft_strlen(line) + 1);
	index = (t_index *)malloc(sizeof(t_index));
	if (!result || !index)
		exit (1);
	index->index = 0;
	index->index2 = 0;
	while (line[index->index])
	{
		if (line[index->index] == '"')
			add_till_next_d_qoute(line, result, index);
		else if (line[index->index] == '\'')
			add_till_next_s_qoute(line, result, index);
		else
		{
			result[index->index2] = line[index->index];
			index->index++;
			index->index2++;
		}
	}
	result[index->index2] = '\0';
	free(index);
	return (result);
}

static void	add_till_next_d_qoute(char *line, char *result, t_index	*index)
{
	index->index++;
	while (line[index->index] != '"' && line[index->index] != '\0')
		result[index->index2++] = line[index->index++];
	if (line[index->index] != '\0')
		index->index++;
}

static void	add_till_next_s_qoute(char *line, char *result, t_index	*index)
{
	index->index++;
	while (line[index->index] != '\'' && line[index->index] != '\0')
		result[index->index2++] = line[index->index++];
	if (line[index->index] != '\0')
		index->index++;
}
