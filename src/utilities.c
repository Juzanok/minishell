/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 09:26:06 by hrings            #+#    #+#             */
/*   Updated: 2022/08/04 12:04:25 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	skip_whitespace(char *line, int index)
{
	int	result;

	result = 0;
	while (line[index + result] == ' ')
		result++;
	return (result);
}

int	is_buildin(char *command)
{
	if (command == NULL)
		return (0);
	if (!ft_strcmp(command, "cd") || !ft_strcmp(command, "export") || \
		!ft_strcmp(command, "unset") || !ft_strcmp(command, "echo") || \
		!ft_strcmp(command, "env") || !ft_strcmp(command, "pwd") || \
		!ft_strcmp(command, "exit"))
		return (1);
	else
		return (0);
}

int	find_end_quote(char *line, int index)
{
	index++;
	while (line[index] != '\'' && line[index] != '\0')
		index++;
	if (line[index] == '\'')
		index++;
	return (index);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	return (0);
}

int	not_redirection_end(char c)
{
	if (c == ' ')
		return (0);
	if (c == '\0')
		return (0);
	if (c == '<')
		return (0);
	if (c == '>')
		return (0);
	return (1);
}
