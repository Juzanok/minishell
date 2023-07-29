/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:54:01 by jkarosas          #+#    #+#             */
/*   Updated: 2022/08/11 11:33:20 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_sorted_env(t_env *env, t_com *com);
static void	print_env(char **env, t_com *com);

void	ft_export(t_minishell *param, t_com *com)
{
	char	*name;
	char	*content;
	int		i;

	if (!com->arg[1])
	{
		export_add_oldpwd(param);
		print_sorted_env(param->env, com);
		return ;
	}
	i = 0;
	while (com->arg[++i])
	{
		name = get_name(com->arg[i]);
		if (not_valid_env_name(name))
			error_export(com, i, name);
		else
		{
			content = get_content(com->arg[i]);
			if (already_exists(param->env, ft_strdup(name), content))
				free(name);
			else
				add_new_env(param->env, name, content);
		}
	}
}

void	add_new_env(t_env *env, char *name, char *content)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = name;
	new->content = content;
	new->next = NULL;
	while (env->next != NULL)
		env = env->next;
	env->next = new;
}

int	already_exists(t_env *env, char *name, char *content)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			free(name);
			if (env->content)
				free(env->content);
			env->content = content;
			return (1);
		}
		env = env->next;
	}
	free(name);
	return (0);
}

static void	print_sorted_env(t_env *env, t_com *com)
{
	char	**str;
	char	*tmp;
	int		len;
	int		i;
	int		j;

	len = envlst_size(env);
	str = env_to_str(env);
	i = -1;
	while (++i < len - 1)
	{
		j = i;
		while (++j < len)
		{
			if (ft_strcmp(str[i], str[j]) > 0)
			{
				tmp = str[i];
				str[i] = str[j];
				str[j] = tmp;
			}
		}
	}
	print_env(str, com);
	free_array(str);
}

static void	print_env(char **env, t_com *com)
{
	int		i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", com->fd_out);
		ft_putstr_fd(env[i], com->fd_out);
		ft_putchar_fd('\n', com->fd_out);
		i++;
	}
}
