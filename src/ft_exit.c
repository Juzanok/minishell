/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:53:58 by jkarosas          #+#    #+#             */
/*   Updated: 2022/08/11 10:49:59 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_not_number(char *str);

void	ft_exit(t_minishell *param, t_com *com)
{
	int	length;

	length = array_length(com->arg);
	if (length == 2 && is_not_number(com->arg[1]))
	{
		printf("minishell: %s: numeric argument required\n", com->arg[0]);
		exit (full_clean_up(param));
	}
	else if (length > 2)
	{
		printf("minishell: exit: too many arguments\n");
		exit (full_clean_up(param));
	}
	else
	{
		if (length == 2)
			param->exit_code = ft_atoi(com->arg[1]) % 256;
		exit (full_clean_up(param));
	}
}

static int	is_not_number(char *str)
{
	int	index;

	index = 0;
	if (str[index] == '-')
		index++;
	while (str[index])
	{
		if (!ft_isdigit(str[index]))
			return (1);
		index++;
	}
	return (0);
}
