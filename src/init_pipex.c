/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:09:27 by hrings            #+#    #+#             */
/*   Updated: 2022/06/20 17:36:14 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// t_pipex	*init_pipex(int num)
// {
// 	t_pipex	*pipex;

// 	pipex = (t_pipex *)malloc(sizeof(t_pipex));
// 	if (!pipex)
// 		exit(1);
// 	pipex->error = 0;
// 	pipex->num_com = num;
// 	return (pipex);
// }

// void	initcommands(t_pipex *pipex, t_minishell *param)
// {
// 	int		index;
// 	t_input	*current;

// 	current = param->input;
// 	pipex->com = (t_parameter **)malloc(sizeof(t_parameter *) * pipex->num_com);
// 	if (!pipex->com)
// 		error_handler_com(pipex, -1);
// 	index = 0;
// 	while (current)
// 	{
// 		pipex->com[index] = (t_parameter *)malloc(sizeof(t_parameter));
// 		if (!pipex->com[index])
// 			error_handler_com(pipex, index);
// 		pipex->com[index]->arg = ft_split_pipex(current->line, ' ');
// 		pipex->com[index]->path = getpath(pipex, pipex->com[index]->arg[0]);
// 		index++;
// 		current = current->next;
// 	}
// }

// void	add_path(t_pipex *pipex, t_minishell *param)
// {
// 		pipex->path = param->path;
// 		pipex->envp = param->envp;
// }
