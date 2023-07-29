/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:31:03 by hrings            #+#    #+#             */
/*   Updated: 2022/08/01 09:55:35 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	run_commands(t_minishell *param)
{
	if (ft_input_size(param->input) != 1)
		run_pipes(param);
	else
		run_single_com(param);
}

void	multi_line_com(t_minishell *param, char *line)
{
	int		index;

	param->commands = ft_split_pipex(line, ';');
	index = 0;
	while (param->commands[index])
	{	
		parser(param, param->commands[index]);
		if (param->input)
			run_commands(param);
		free_list(param);
		index++;
	}
	free_array(param->commands);
	param->commands = NULL;
}
