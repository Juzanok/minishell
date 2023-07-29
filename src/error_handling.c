/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 09:16:13 by hrings            #+#    #+#             */
/*   Updated: 2022/08/03 16:30:50 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error_parser(t_minishell *param, int error_num, char c)
{
	if (error_num == PARSEPIPE)
	{
		printf("minishell: syntax error near unexpected token %c\n", c);
		param->exit_code = error_num;
		free_list_com(param);
	}
}

void	error_handler_pip(t_minishell *param)
{
	int	exit_code;

	perror("Minishell: ");
	param->exit_code = 1;
	exit_code = full_clean_up(param);
	exit(exit_code);
}

void	error_export(t_com *com, int i, char *name)
{
	printf("Minishell: export: %s: not a valid identifier\n", com->arg[i]);
	com->error = 1;
	free(name);
}

void	error_unset(t_com *com, int i)
{
	printf("Minishell: unset: %s: not a valid identifier\n", com->arg[i]);
	com->error = 1;
}
