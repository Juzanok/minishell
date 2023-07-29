/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_coms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 09:54:51 by hrings            #+#    #+#             */
/*   Updated: 2022/07/13 12:13:43 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_coms	*listnew_coms(t_com *com);
static void		add_to_end_list_com(t_minishell *param, t_com *com);

void	list_coms_push(t_minishell *param, t_com	*com)
{
	if (!param->coms)
	{
		param->coms = listnew_coms(com);
	}
	else
		add_to_end_list_com(param, com);
}

static t_coms	*listnew_coms(t_com *com)
{
	t_coms	*new_lst;

	new_lst = (t_coms *)malloc(sizeof(t_coms));
	if (!new_lst)
		return (NULL);
	new_lst->com = com;
	new_lst->next = NULL;
	return (new_lst);
}

void	free_list_com(t_minishell *param)
{
	t_coms	*current;
	t_coms	*next;

	next = param->coms;
	while (next)
	{
		current = next;
		next = next->next;
		clean_up_com(current->com);
		free(current);
	}
	param->coms = NULL;
}

static void	add_to_end_list_com(t_minishell *param, t_com *com)
{
	t_coms	*current;

	current = param->coms;
	while (current->next)
		current = current->next;
	current->next = listnew_coms(com);
	if (!current->next)
		exit(1);
}
