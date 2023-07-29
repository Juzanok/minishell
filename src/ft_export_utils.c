/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:05:22 by jkarosas          #+#    #+#             */
/*   Updated: 2022/08/11 10:20:58 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env_exists(t_env *env, char *name)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	export_add_oldpwd(t_minishell *param)
{
	if (env_exists(param->env, "OLDPWD") == 0)
		add_new_env(param->env, ft_strdup("OLDPWD"), NULL);
}

char	*ft_combine_strings(char *str1, char *str2, char *str3)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(str1, str2);
	result = ft_strjoin(tmp, str3);
	free(tmp);
	free(str1);
	free(str2);
	free(str3);
	return (result);
}
