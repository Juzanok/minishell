/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_com_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 09:25:04 by hrings            #+#    #+#             */
/*   Updated: 2022/07/18 11:22:38 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	init_com(t_com *com);
static int	parse_command(t_com *result, char *line, int index);
static void	add_to_com_line(t_com *result, char *line, int index, int len);

t_com	*parse_com_line(char *line)
{
	t_com	*result;
	int		index;

	result = (t_com *)malloc(sizeof(t_com));
	if (!result)
		return (NULL);
	init_com(result);
	index = 0;
	while (line[index] != '\0' && !result->error)
	{
		index += skip_whitespace(line, index);
		if (line[index] == '<' || line[index] == '>')
			index += parse_redirect(result, line, index);
		else
			index += parse_command(result, line, index);
	}
	return (result);
}

static void	init_com(t_com *com)
{
	com->com_line = NULL;
	com->redirect = NULL;
	com->arg = NULL;
	com->path = NULL;
	com->red_input = 0;
	com->red_output = 0;
	com->error = 0;
	com->fd_in = STDIN_FILENO;
	com->fd_out = STDOUT_FILENO;
}

static int	parse_command(t_com *result, char *line, int index)
{
	int	i;

	i = 0;
	while (line[index + i] != '<' && line[index + i] != '>' && \
			line[index + i] != '\0')
		i = index_add(line, index, i);
	if (result->com_line == NULL)
		result->com_line = ft_substr(line, index, i);
	else
		add_to_com_line(result, line, index, i);
	return (i);
}

static void	add_to_com_line(t_com *com, char *line, int index, int len)
{
	char	*result;
	char	*tmp;

	tmp = ft_substr(line, index, len);
	result = ft_strjoin(com->com_line, tmp);
	free(tmp);
	free(com->com_line);
	com->com_line = result;
}
