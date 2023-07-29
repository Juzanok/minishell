/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 19:46:23 by jkarosas          #+#    #+#             */
/*   Updated: 2022/08/11 10:24:27 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_with_content(t_env *env, t_com *com);
static void	print_without_content(t_env *env, t_com *com);

void	ft_env(t_env *env, t_com *com)
{
	if (com->arg[1])
	{
		printf("env: \'%s\': Permission denied\n", com->arg[1]);
		com->error = 126;
		return ;
	}
	while (env != NULL)
	{
		if (env->content)
			print_with_content(env, com);
		else
			print_without_content(env, com);
		env = env->next;
	}
}

static void	print_with_content(t_env *env, t_com *com)
{
	char	*env_str;

	ft_putstr_fd(env->name, com->fd_out);
	ft_putchar_fd('=', com->fd_out);
	env_str = remove_quote(env->content);
	ft_putstr_fd(env_str, com->fd_out);
	free(env_str);
	ft_putchar_fd('\n', com->fd_out);
}

static void	print_without_content(t_env *env, t_com *com)
{
	ft_putstr_fd(env->name, com->fd_out);
	ft_putchar_fd('\n', com->fd_out);
}
