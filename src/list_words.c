/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:11:40 by hrings            #+#    #+#             */
/*   Updated: 2022/07/27 10:27:51 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	t_words	*new_word_list(t_minishell *param, char *word);
static void		add_to_list(t_minishell *param, t_words *listwords, char *word);

void	list_word_add(t_minishell *param, t_words *words, char *word)
{
	if (!words->oldword)
	{
		words->oldword = ft_strdup(word);
		if (ft_isdigit(word[0]))
			words->newword = ft_strdup("");
		else if (ft_strcmp(word, "?") == 0)
			words->newword = ft_itoa(param->exit_code);
		else
			words->newword = find_env(param, word);
		if (!words->newword)
			words->newword = ft_strdup("");
		words->count = 1;
		words->next = NULL;
	}
	else
		add_to_list(param, words, word);
}

void	free_words(t_words *words)
{
	t_words	*current;
	t_words	*next;

	next = words;
	while (next)
	{
		current = next;
		next = next->next;
		free(current->oldword);
		free(current->newword);
		free(current);
	}
}

int	find_new_line_len(char *line, t_words *words)
{
	int		result;
	t_words	*current;
	int		newlen;
	int		oldlen;

	result = ft_strlen(line);
	current = words;
	while (current)
	{
		newlen = ft_strlen(current->newword);
		oldlen = ft_strlen(current->oldword);
		result += (newlen - oldlen) * current->count;
		current = current->next;
	}
	return (result + 1);
}

static	t_words	*new_word_list(t_minishell *param, char *word)
{
	t_words	*new_lst;

	new_lst = (t_words *)malloc(sizeof(t_words));
	if (!new_lst)
		return (NULL);
	new_lst->oldword = ft_strdup(word);
	if (ft_isdigit(word[0]))
		new_lst->newword = ft_strdup("");
	else if (ft_strcmp(word, "?") == 0)
		new_lst->newword = ft_itoa(param->exit_code);
	else
		new_lst->newword = find_env(param, word);
	if (!new_lst->newword)
		new_lst->newword = ft_strdup("");
	new_lst->count = 1;
	new_lst->next = NULL;
	return (new_lst);
}

static void	add_to_list(t_minishell *param, t_words *listwords, char *word)
{
	t_words	*current;

	current = listwords;
	while (current->next)
	{
		if (ft_strcmp(word, current->oldword) == 0)
		{
			current->count++;
			return ;
		}
		current = current->next;
	}
	current->next = new_word_list(param, word);
	if (!current->next)
		exit(1);
}
