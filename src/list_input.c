/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 09:54:24 by hrings            #+#    #+#             */
/*   Updated: 2022/06/22 13:49:14 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	add_to_end_list(t_minishell *param, char *line);

t_input	*ft_listnew(char *line)
{
	t_input	*new_lst;

	new_lst = (t_input *)malloc(sizeof(t_input));
	if (!new_lst)
		return (NULL);
	new_lst->line = line;
	new_lst->next = NULL;
	return (new_lst);
}

void	list_push(t_minishell *param, char *line)
{
	if (!param->input)
	{
		param->input = ft_listnew(line);
	}
	else
		add_to_end_list(param, line);
}

static void	add_to_end_list(t_minishell *param, char *line)
{
	t_input	*current;

	current = param->input;
	while (current->next)
		current = current->next;
	current->next = ft_listnew(line);
	if (!current->next)
		exit(1);
}

void	free_list(t_minishell *param)
{
	t_input	*current;
	t_input	*next;

	next = param->input;
	while (next)
	{
		current = next;
		next = next->next;
		free(current->line);
		free(current);
	}
	param->input = NULL;
}

int	ft_input_size(t_input *lst)
{
	int		length;

	length = 0;
	while (lst)
	{
		lst = lst->next;
		length++;
	}
	return (length);
}
