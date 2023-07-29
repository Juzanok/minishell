/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 11:04:47 by hrings            #+#    #+#             */
/*   Updated: 2022/07/27 10:26:34 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	replace_words(char *line, t_words *words, char *result);
static void	work_in_s_quote(t_index	*index, char *line, char *result);
static void	in_d_quote(t_words *words, t_index	*i, char *line, char *result);

char	*replace_word(char *line, t_words *words)
{
	char	*result;
	int		newlen;

	if (words->oldword)
	{
		newlen = find_new_line_len(line, words);
		result = (char *)ft_calloc(newlen, sizeof(char));
		if (!result)
			exit(1);
		replace_words(line, words, result);
		free(line);
		free_words(words);
		return (result);
	}
	else
	{
		free(words);
		return (line);
	}
}

static void	replace_words(char *line, t_words *words, char *result)
{
	t_index	*i;
	t_words	*word;

	i = (t_index *)malloc(sizeof(t_index));
	if (!i)
		exit(1);
	i->index = 0;
	i->index2 = 0;
	while (line && line[i->index2])
	{
		if (line[i->index2] == '\'')
			work_in_s_quote(i, line, result);
		else if (line[i->index2] == '"')
			in_d_quote(words, i, line, result);
		else if (line[i->index2] == '$' && var_start(line[i->index2 + 1]))
		{
			word = is_in_line(line, words, i->index2 + 1);
			add_new_word(result, word->newword, i->index);
			i->index2 += ft_strlen(word->oldword) + 1;
			i->index += ft_strlen(word->newword);
		}
		else
			result[i->index++] = line[i->index2++];
	}
	free(i);
}

static void	work_in_s_quote(t_index	*index, char *line, char *result)
{
	result[index->index++] = line[index->index2++];
	while (line[index->index2] != '\'')
		result[index->index++] = line[index->index2++];
	result[index->index++] = line[index->index2++];
}

static void	in_d_quote(t_words *words, t_index	*i, char *line, char *result)
{
	t_words	*word;

	result[i->index++] = line[i->index2++];
	while (line[i->index2] != '"')
	{	
		if (line[i->index2] == '$' && var_start_in_quote(line[i->index2 + 1]))
		{
			word = is_in_line(line, words, i->index2 + 1);
			add_new_word(result, word->newword, i->index);
			i->index2 += ft_strlen(word->oldword) + 1;
			i->index += ft_strlen(word->newword);
		}
		else
			result[i->index++] = line[i->index2++];
	}
	result[i->index++] = line[i->index2++];
}
