/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:31:57 by hrings            #+#    #+#             */
/*   Updated: 2022/07/08 10:01:56 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	first_com(t_minishell *param, t_com *com);
static void	middle_com(t_minishell *param, t_com *com);
static void	last_com(t_minishell *param, t_com *com);

void	redirect(t_minishell *param, t_com *com)
{
	if (com->index == 0)
		first_com(param, com);
	else if (com->index == (param->num_com - 1))
		last_com(param, com);
	else
		middle_com(param, com);
	close_pipes(param);
}

void	open_redirections(t_minishell *param, t_com *com)
{
	t_redirect	*cur;

	cur = com->redirect;
	while (cur)
	{
		if (cur->redir == REDIRECT_INPUT || cur->redir == HERE_DOC)
		{
			open_input(param, com, cur);
			com->red_input = 1;
		}
		else if (cur->redir == REDIRECT_OVER || cur->redir == REDIRECT_APPEND)
		{
			open_output(param, com, cur);
			com->red_output = 1;
		}
		if (com->error)
			break ;
	cur = cur->next;
	}
}

static void	first_com(t_minishell *param, t_com *com)
{
	if (com->red_input)
		dup2(com->fd_in, STDIN_FILENO);
	if (com->red_output)
		dup2(com->fd_out, STDOUT_FILENO);
	else
	{
		dup2(param->pipes[1], STDOUT_FILENO);
	}
}

static void	middle_com(t_minishell *param, t_com *com)
{
	if (com->red_input)
		dup2(com->fd_in, STDIN_FILENO);
	else
		dup2(param->pipes[com->index * 2 - 2], STDIN_FILENO);
	if (com->red_output)
		dup2(com->fd_out, STDOUT_FILENO);
	else
		dup2(param->pipes[2 * com->index + 1], STDOUT_FILENO);
}

static void	last_com(t_minishell *param, t_com *com)
{
	if (com->red_input)
		dup2(com->fd_in, STDIN_FILENO);
	else
		dup2(param->pipes[com->index * 2 - 2], STDIN_FILENO);
	if (com->red_output)
		dup2(com->fd_out, STDOUT_FILENO);
}
