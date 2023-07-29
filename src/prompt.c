/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:41:14 by hrings            #+#    #+#             */
/*   Updated: 2022/08/11 12:57:58 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*build_prompt(t_minishell *param);
static char	*build_prompt_replace(t_minishell *param, char *home);
//static int	already_exists(t_env *env, char *name, char *content);

char	*display_prompt(t_minishell *param)
{
	char	*tmp;
	char	*home;
	char	*result;

	tmp = find_env(param, "HOME");
	home = remove_quote(tmp);
	free(tmp);
	if (ft_strlen(home) == 0 || \
		(ft_strncmp(param->pwd, home, ft_strlen(home)) != 0))
		tmp = build_prompt(param);
	else
		tmp = build_prompt_replace(param, home);
	result = remove_quote(tmp);
	free(tmp);
	free(home);
	return (result);
}

void	set_pwd(t_minishell *param)
{
	char	*tmp;
	char	*pwd;

	tmp = getcwd(NULL, 0);
	if (tmp)
	{
		pwd = ft_combine_strings(ft_strdup("\""), ft_strdup(tmp), \
		ft_strdup("\""));
		already_exists(param->env, ft_strdup("PWD"), pwd);
		if (param->pwd)
			free(param->pwd);
		param->pwd = tmp;
	}
}

static char	*build_prompt(t_minishell *param)
{
	char	*tmp;
	char	*tmp2;
	char	*result;

	tmp = ft_strjoin(param->user, ":");
	tmp2 = ft_strjoin(param->pwd, "$ ");
	result = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	return (result);
}

static char	*build_prompt_replace(t_minishell *param, char *home)
{
	char	*tmp;
	char	*tmp2;
	char	*dir;
	char	*result;

	tmp = ft_strjoin(param->user, ":");
	dir = ft_strjoin("~", param->pwd + ft_strlen(home));
	tmp2 = ft_strjoin(dir, "$ ");
	result = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	free(dir);
	return (result);
}

// static int	already_exists(t_env *env, char *name, char *content)
// {
// 	while (env != NULL)
// 	{
// 		if (ft_strcmp(env->name, name) == 0)
// 		{
// 			if (env->content)
// 				free(env->content);
// 			env->content = content;
// 			return (1);
// 		}
// 		env = env->next;
// 	}
// 	return (0);
// }
