/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 19:46:21 by jkarosas          #+#    #+#             */
/*   Updated: 2022/08/02 09:22:24 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_n_flag(char *arg);

void	ft_echo(t_com *com)
{
	int	n_flag;
	int	len;
	int	i;

	len = array_length(com->arg);
	n_flag = 0;
	i = 1;
	if (len > 1)
	{
		while (com->arg[i] && is_n_flag(com->arg[i]))
		{
			n_flag = 1;
			i++;
		}
		while (com->arg[i])
		{
			ft_putstr_fd(com->arg[i], com->fd_out);
			if (com->arg[i + 1])
				ft_putchar_fd(' ', com->fd_out);
			i++;
		}
	}
	if (n_flag == 0)
		ft_putchar_fd('\n', com->fd_out);
}

static int	is_n_flag(char *arg)
{
	int	index;

	index = 0;
	if (arg[index++] != '-')
		return (0);
	if (arg[index++] != 'n')
		return (0);
	while (arg[index] == 'n')
		index++;
	if (arg[index] == '\0')
		return (1);
	return (0);
}
