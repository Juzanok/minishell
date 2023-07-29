/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:05:24 by hrings            #+#    #+#             */
/*   Updated: 2022/08/03 13:17:00 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_word(char *line, int index);
static int	not_end_of_word(char *line, int index);
static int	in_d_quote(t_minishell *param, t_words *words, char *line, int i);

char	*expand_env(t_minishell *param, char *line)
{
	char	*oldword;
	t_words	*words;
	int		index;

	words = (t_words *)malloc(sizeof(t_words));
	words->oldword = NULL;
	index = 0;
	while (line[index])
	{
		if (line[index] == '\'')
			index = find_end_quote(line, index);
		else if (line[index] == '"')
			index = in_d_quote(param, words, line, index);
		else if (line[index] == '$' && var_start(line[index + 1]))
		{
			oldword = get_word(line, index);
			list_word_add(param, words, oldword);
			index += ft_strlen(oldword) + 1;
			free(oldword);
		}
		else
			index++;
	}
	line = replace_word(line, words);
	return (line);
}

static int	in_d_quote(t_minishell *param, t_words *words, char *line, int i)
{
	char	*oldword;

	i++;
	while (line[i] && line[i] != '"')
	{
		if (line[i] == '$' && var_start_in_quote(line[i + 1]))
		{
			oldword = get_word(line, i);
			list_word_add(param, words, oldword);
			i += ft_strlen(oldword) + 1;
			free(oldword);
		}
		else
			i++;
	}
	return (i);
}

static char	*get_word(char *line, int index)
{
	int	len;
	int	start_index;

	start_index = index;
	len = 1;
	if (ft_isdigit(line[start_index + len]) || line[start_index + len] == '?')
		return (ft_substr(line, start_index + 1, len));
	if (line[start_index + len] == '\'' || line[start_index + len] == '\"')
		return (ft_strdup(""));
	while (not_end_of_word(line, start_index + len))
		len = index_add(line, index, len);
	return (ft_substr(line, start_index + 1, len - 1));
}

static int	not_end_of_word(char *line, int index)
{
	if (line[index] == ' ')
		return (0);
	else if (line[index] == '\0')
		return (0);
	else if (line[index] == '\"')
		return (0);
	else if (line[index] == '\'')
		return (0);
	else if (!(ft_isalnum(line[index]) || line[index] == '_'))
		return (0);
	return (1);
}
