/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:10:06 by hrings            #+#    #+#             */
/*   Updated: 2022/07/14 08:44:54 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	child(t_minishell *param, t_com *com)
{
	if (!com->error)
	{
		if (com->red_input)
			redirect_input(com);
		if (com->red_output)
			redirect_output(com);
		runshellcmd(param, com);
	}
	else
		exit(full_clean_up_com(param, com));
}
