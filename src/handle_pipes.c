/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:30:29 by hrings            #+#    #+#             */
/*   Updated: 2022/07/15 09:21:22 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	build_arg_path(t_minishell *param, t_com *com);

void	creat_pipes(t_minishell *param)
{
	int	index;

	param->pipes = (int *)malloc(sizeof(int) * 2 * (param->num_com - 1));
	if (!param->pipes)
		error_handler_pip(param);
	index = 0;
	while (index < (param->num_com - 1))
	{
		if (pipe(param->pipes + 2 * index) < 0)
			error_handler_pip(param);
		index++;
	}
}

void	close_pipes(t_minishell *param)
{
	int	index;

	index = 0;
	while (index < (2 * (param->num_com - 1)))
	{
		close(param->pipes[index]);
		index++;
	}
}

void	prepare_pipes(t_minishell *param)
{
	t_input	*current;
	t_com	*com;
	int		index;

	index = 0;
	current = param->input;
	while (current)
	{
		com = parse_com_line(current->line);
		com->index = index++;
		if (!com->error)
			open_redirections(param, com);
		if (!com->error)
			build_arg_path(param, com);
		list_coms_push(param, com);
		current = current->next;
	}
}

static void	build_arg_path(t_minishell *param, t_com *com)
{
	com->com_line = expand_env(param, com->com_line);
	com->arg = ft_split_pipex(com->com_line, ' ');
	quote_handling(com);
	if (!is_buildin(com->arg[0]))
		com->path = getpath(param, com, com->arg[0]);
}
