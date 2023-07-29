/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:10:38 by hrings            #+#    #+#             */
/*   Updated: 2022/08/10 12:24:58 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	cleanup(t_minishell *param);

int	full_clean_up(t_minishell *param)
{
	int	result;

	result = param->exit_code;
	if (param->pipes)
	{
		close_pipes(param);
		free(param->pipes);
		param->pipes = NULL;
	}
	if (param->coms)
		free_list_com(param);
	if (param->env)
		free_env(param);
	if (param->input)
		free_list(param);
	cleanup(param);
	return (result);
}

int	full_clean_up_com(t_minishell *param, t_com *com)
{
	int	result;

	result = com->error;
	if (param->pipes)
	{
		close_pipes(param);
		free(param->pipes);
		param->pipes = NULL;
	}
	if (param->coms)
		free_list_com(param);
	if (param->env)
		free_env(param);
	if (param->input)
		free_list(param);
	cleanup(param);
	return (result);
}

void	clean_up_com(t_com *com)
{
	int	index;

	index = 0;
	free_list_redirect(com);
	if (com->com_line)
	{
		while (com->arg && com->arg[index])
			free(com->arg[index++]);
		free(com->com_line);
		free(com->arg);
		if (com->path)
			free(com->path);
	}
	free(com);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static void	cleanup(t_minishell *param)
{
	int	index;

	index = 0;
	if (param->path)
	{
		while (param->path[index])
			free(param->path[index++]);
		free(param->path);
	}
	if (param->commands)
		free_array(param->commands);
	if (param->user)
		free(param->user);
	if (param->pwd)
		free(param->pwd);
	free(param);
}
