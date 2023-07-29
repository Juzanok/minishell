/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:29:06 by hrings            #+#    #+#             */
/*   Updated: 2022/06/24 13:51:26 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void			add_end_red(t_com *com, char *line, int redir, char *delim);
static t_redirect	*list_new_redirect(char *input, int redirect, char *delim);

void	list_push_redirect(t_com *com, char *line, int redirect, char *delim)
{
	if (!com->redirect)
	{
		com->redirect = list_new_redirect(line, redirect, delim);
	}
	else
		add_end_red(com, line, redirect, delim);
}

static t_redirect	*list_new_redirect(char *input, int redirect, char *delim)
{
	t_redirect	*new_lst;

	new_lst = (t_redirect *)malloc(sizeof(t_redirect));
	if (!new_lst)
		return (NULL);
	new_lst->file = input;
	new_lst->delim = delim;
	new_lst->redir = redirect;
	new_lst->next = NULL;
	return (new_lst);
}

static void	add_end_red(t_com *com, char *line, int redirect, char *delim)
{
	t_redirect	*current;

	current = com->redirect;
	while (current->next)
		current = current->next;
	current->next = list_new_redirect(line, redirect, delim);
	if (!current->next)
		exit(1);
}

void	free_list_redirect(t_com *com)
{
	t_redirect	*current;
	t_redirect	*next;

	next = com->redirect;
	while (next)
	{
		current = next;
		next = next->next;
		free(current->file);
		free(current);
	}
	com->redirect = NULL;
}

// int	ft_input_size(t_input *lst)
// {
// 	int		length;

// 	length = 0;
// 	while (lst)
// 	{
// 		lst = lst->next;
// 		length++;
// 	}
// 	return (length);
// }
