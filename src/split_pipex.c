/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:06:00 by hrings            #+#    #+#             */
/*   Updated: 2022/07/15 09:16:08 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	find_number_words(char const *s, char c);
static void		add_word(char const *s, char c, size_t n_words, char **result);
static int		findendword(char const *s, char c);

char	**ft_split_pipex(char const *s, char c)
{
	char	**result;
	size_t	n_words;

	if (!s)
		return (NULL);
	if (!*s)
	{
		result = (char **)malloc(1 * sizeof(char *));
		if (!result)
			return (NULL);
		result[0] = 0;
		return (result);
	}
	n_words = find_number_words(s, c);
	result = (char **)malloc((n_words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	add_word(s, c, n_words, result);
	return (result);
}

static void	add_word(char const *s, char c, size_t n_words, char **result)
{
	size_t	size_word;
	size_t	index;
	size_t	index_2;

	index = 0;
	index_2 = 0;
	while (index_2 < n_words && *s)
	{
		while (s[index] == c && s[index] != '\0')
			index++;
		size_word = findendword(s + index, c);
		result[index_2++] = ft_substr(s + index, 0, size_word);
		index += size_word;
	}
	result[index_2] = 0;
}

static size_t	find_number_words(char const *s, char c)
{
	size_t	result;

	result = 0;
	while (*s == c)
		s++;
	while (*s)
	{
		result++;
		s += findendword(s, c);
		while (*s == c && *s != '\0')
			s++;
	}
	return (result);
}

static int	findendword(char const *s, char c)
{
	int	result;

	result = 0;
	while (s[result] != c && s[result] != '\0')
	{
		if (s[result] == '\'')
		{
			result++;
			while (s[result] != '\'' && s[result] != '\0')
				result++;
		}
		if (s[result] == '\"')
		{
			result++;
			while (s[result] != '\"' && s[result] != '\0')
				result++;
		}
		if (s[result] == '\0')
			return (result);
		result++;
	}
	return (result);
}
