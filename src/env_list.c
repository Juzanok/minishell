/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:43:36 by jkarosas          #+#    #+#             */
/*   Updated: 2022/08/11 10:19:58 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_env(t_minishell *param, char **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return ;
	env->name = get_name(envp[0]);
	env->content = get_content(envp[0]);
	env->next = NULL;
	param->env = env;
	i = 1;
	while (envp && envp[0] && envp[i])
	{
		new = (t_env *)malloc(sizeof(t_env));
		if (!new)
			return ;
		new->name = get_name(envp[i]);
		new->content = get_content(envp[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
}

char	*get_name(char *str)
{
	char	*value;
	int		start;
	int		end;
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	start = i;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	end = i;
	value = ft_substr(str, start, end - start);
	return (value);
}

char	*get_content(char *str)
{
	char	*value;
	int		start;
	int		end;
	int		i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (NULL);
	start = i + 1;
	i = start;
	while (str[i])
		i++;
	end = i;
	value = ft_combine_strings(ft_strdup("\""), \
			ft_substr(str, start, end - start), ft_strdup("\""));
	return (value);
}

char	*find_env(t_minishell *param, char *oldword)
{
	t_env	*current;

	current = param->env;
	while (current)
	{
		if (ft_strcmp(current->name, oldword) == 0)
		{
			if (current->content)
				return (ft_strdup(current->content));
			else
				return (NULL);
		}
		current = current->next;
	}
	return (ft_strdup(""));
}

void	free_env(t_minishell *param)
{
	t_env	*list;

	while (param->env != NULL)
	{
		list = param->env;
		param->env = param->env->next;
		free(list->name);
		if (list->content)
			free(list->content);
		free(list);
	}
}
