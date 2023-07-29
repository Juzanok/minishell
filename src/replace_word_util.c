/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_word_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:38:25 by hrings            #+#    #+#             */
/*   Updated: 2022/08/03 13:13:08 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	var_start(char c)
{
	if (ft_isalnum(c))
		return (1);
	if (c == '?')
		return (1);
	if (c == '\'')
		return (1);
	if (c == '"')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

int	var_start_in_quote(char c)
{
	if (ft_isalnum(c))
		return (1);
	if (c == '?')
		return (1);
	if (c == '\'')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

void	add_new_word(char *result, char *new, int index)
{
	int		indexword;

	indexword = 0;
	while (new[indexword])
	{
		result[index + indexword] = new[indexword];
		indexword++;
	}
}

t_words	*is_in_line(char *line, t_words *words, int i)
{
	int		index;
	t_words	*cur;

	cur = words;
	while (cur)
	{
		index = 0;
		if (ft_strcmp(cur->oldword, "?") == 0 && (line[index + i] == '?'))
			return (cur);
		if (ft_isdigit(cur->oldword[0]) && line[index + i] == cur->oldword[0])
			return (cur);
		if ((ft_strlen(cur->oldword) == 0) && \
			((line[index + i] == '\'') || (line[index + i] == '\"')))
			return (cur);
		while ((line[index + i] == cur->oldword[index]) && cur->oldword[index])
			index++;
		if (!ft_isalnum(line[index + i]) && cur->oldword[index] == '\0')
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}
