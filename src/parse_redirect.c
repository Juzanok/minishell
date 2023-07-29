/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:01:55 by hrings            #+#    #+#             */
/*   Updated: 2022/07/19 08:16:30 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	parse_redirect_over(t_com *result, char *line, int index);
static int	parse_redirect_append(t_com *result, char *line, int index);
static int	parse_redirect_input(t_com *result, char *line, int index);
static int	parse_redirect_here_doc(t_com *result, char *line, int index);

int	parse_redirect(t_com *result, char *line, int index)
{
	int	i;

	i = 1;
	if (line[index] == '>' && line[index + 1] != '>')
		i = parse_redirect_over(result, line, index);
	else if (line[index] == '>' && line[index + 1] == '>')
		i = parse_redirect_append(result, line, index);
	else if (line[index] == '<' && line[index + 1] != '<')
		i = parse_redirect_input(result, line, index);
	else if (line[index] == '<' && line[index + 1] == '<')
		i = parse_redirect_here_doc(result, line, index);
	return (i);
}

static int	parse_redirect_over(t_com *result, char *line, int index)
{
	int		i;
	int		white;
	char	*file;

	i = 1;
	white = skip_whitespace(line, index + 1);
	i += white;
	while (not_redirection_end(line[index + i]))
		i = index_add(line, index, i);
	if ((i - white - 1) == 0)
	{
		result->error = REDIRECTERROR;
		printf("minishell: syntax error near unexpected token %c\n", \
			line[index + i]);
	}
	else
	{
		file = ft_substr(line, index + white + 1, i - white - 1);
		list_push_redirect(result, file, REDIRECT_OVER, NULL);
	}
	return (i);
}

static int	parse_redirect_append(t_com *result, char *line, int index)
{
	int		i;
	int		white;
	char	*file;

	i = 2;
	white = skip_whitespace(line, index + i);
	i += white;
	while (not_redirection_end(line[index + i]))
		i = index_add(line, index, i);
	if ((i - white - 2) == 0)
	{
		result->error = REDIRECTERROR;
		printf("minishell: syntax error near unexpected token %c\n", \
			line[index + i]);
	}
	else
	{
		file = ft_substr(line, index + white + 2, i - white - 2);
		list_push_redirect(result, file, REDIRECT_APPEND, NULL);
	}
	return (i);
}

static int	parse_redirect_input(t_com *result, char *line, int index)
{
	int		i;
	int		white;
	char	*file;

	i = 1;
	white = skip_whitespace(line, index + i);
	i += white;
	while (not_redirection_end(line[index + i]))
		i = index_add(line, index, i);
	if ((i - white - 1) == 0)
	{
		result->error = REDIRECTERROR;
		printf("minishell: syntax error near unexpected token %c\n", \
			line[index + i]);
	}
	else
	{
		file = ft_substr(line, index + white + 1, i - white - 1);
		list_push_redirect(result, file, REDIRECT_INPUT, NULL);
	}
	return (i);
}

static int	parse_redirect_here_doc(t_com *result, char *line, int index)
{
	int		i;
	int		white;
	char	*delimiter;

	i = 2;
	white = skip_whitespace(line, index + i);
	i += white;
	while (not_redirection_end(line[index + i]))
		i = index_add(line, index, i);
	if ((i - white - 2) == 0)
	{
		result->error = REDIRECTERROR;
		printf("minishell: syntax error near unexpected token %c\n", \
			line[index + i]);
	}
	else
	{
		delimiter = ft_substr(line, index + white + 2, i - white - 2);
		list_push_redirect(result, NULL, HERE_DOC, delimiter);
	}
	return (i);
}
