/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 19:46:27 by jkarosas          #+#    #+#             */
/*   Updated: 2022/08/11 10:42:42 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_pwd(t_minishell *param, t_com *com)
{
	ft_putstr_fd(param->pwd, com->fd_out);
	ft_putstr_fd("\n", com->fd_out);
}
