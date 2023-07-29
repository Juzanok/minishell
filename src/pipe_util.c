/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:00:16 by hrings            #+#    #+#             */
/*   Updated: 2022/07/16 10:07:01 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*joinpath(char *directory, char *command)
{
	char	*result;
	char	*tmp;

	tmp = ft_strjoin(directory, "/");
	result = ft_strjoin(tmp, command);
	free(tmp);
	return (result);
}

char	*getpath(t_minishell *param, t_com *com, char *command)
{
	char	*result;
	int		index;

	index = 0;
	initpath(param);
	if (access(command, F_OK) == 0)
		return (ft_strdup(command));
	while (param->path && param->path[index])
	{
		result = joinpath(param->path[index], command);
		if (access(result, F_OK) == 0)
			return (result);
		free(result);
		index++;
	}
	printf("Minishell: %s : command not found\n", command);
	com->error = 127;
	return (ft_strdup(command));
}

int	ft_strfind(char *str, char c)
{
	int	result;

	result = 0;
	while (str[result] && str[result] != c)
		result++;
	if (!str[result])
		return (-1);
	else
		return (result);
}
