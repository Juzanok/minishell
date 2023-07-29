/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:54:04 by jkarosas          #+#    #+#             */
/*   Updated: 2022/08/03 16:31:10 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_existance(t_env *env, char *arg);
static void	del_node(t_minishell *param, int pos);
static void	free_node(t_env *env);

void	ft_unset(t_minishell *param, t_com *com)
{
	int	index;
	int	i;

	if (!com->arg[1])
		return ;
	index = 1;
	while (com->arg[index])
	{
		if (not_valid_env_name(com->arg[index]))
			error_unset(com, index);
		else
		{
			i = check_existance(param->env, com->arg[index]);
			if (i >= 0)
				del_node(param, i);
		}
		index++;
	}
}

static void	del_node(t_minishell *param, int pos)
{
	t_env	*temp;
	t_env	*prev;
	int		i;

	i = 0;
	temp = param->env;
	if (temp != NULL && pos == 0)
	{
		param->env = temp->next;
		free_node(temp);
		return ;
	}
	while (temp != NULL && i != pos)
	{
		prev = temp;
		temp = temp->next;
		i++;
	}
	prev->next = temp->next;
	free_node(temp);
}

static int	check_existance(t_env *env, char *arg)
{
	int	i;

	i = 0;
	while (env && env->next != NULL)
	{
		if (ft_strcmp(env->name, arg) == 0)
			return (i);
		env = env->next;
		i++;
	}
	if (ft_strcmp(env->name, arg) == 0)
		return (i);
	return (-1);
}

static void	free_node(t_env *env)
{
	free(env->name);
	free(env->content);
	free(env);
}
