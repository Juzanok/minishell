/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 08:33:31 by hrings            #+#    #+#             */
/*   Updated: 2022/08/11 10:24:45 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	open_d_quote(char *line, t_checker *checker);
static void	open_s_quote(char *line, t_checker *checker);

int	quote_checker(char *line)
{
	t_checker	*checker;
	int			result;

	checker = (t_checker *)malloc(sizeof(t_checker));
	if (!checker)
		return (0);
	checker->index = 0;
	checker->result = 1;
	while (line[checker->index] != '\0')
	{
		if (line[checker->index] == '\"')
			open_d_quote(line, checker);
		else if (line[checker->index] == '\'')
			open_s_quote(line, checker);
		else
			checker->index++;
	}
	result = checker->result;
	if (!result)
		printf ("Quotation error, missing closing quotation \n");
	free(checker);
	return (result);
}

static void	open_d_quote(char *line, t_checker *checker)
{
	int	closed;

	closed = 1;
	checker->index += 1;
	while (line[checker->index] != '\0')
	{
		if (line[checker->index] == '\"')
		{
			checker->index += 1;
			closed = 0;
			break ;
		}
		else
			checker->index++;
	}
	if (closed)
		checker->result = 0;
}

static void	open_s_quote(char *line, t_checker *checker)
{
	int	closed;

	closed = 1;
	checker->index += 1;
	while (line[checker->index] != '\0')
	{
		if (line[checker->index] == '\'')
		{
			checker->index += 1;
			closed = 0;
			break ;
		}
		else
			checker->index++;
	}
	if (closed)
		checker->result = 0;
}
