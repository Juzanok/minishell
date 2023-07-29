/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:25:59 by jkarosas          #+#    #+#             */
/*   Updated: 2022/08/11 13:54:12 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	change_dir(t_minishell *param, t_com *com, char *path);
static void	change_to_home(t_minishell *param, t_com *com);
static void	change_to_last(t_minishell *param, t_com *com);

void	ft_cd(t_minishell *param, t_com *com)
{
	if (array_length(com->arg) > 2)
	{
		printf("cd: too many arguments\n");
		com->error = 1;
	}
	else if (array_length(com->arg) == 1)
		change_to_home(param, com);
	else if (ft_strcmp(com->arg[1], "-") == 0)
		change_to_last(param, com);
	else if (ft_strcmp(com->arg[1], "~") == 0)
		change_to_home(param, com);
	else
		change_dir(param, com, com->arg[1]);
}

static void	change_to_last(t_minishell *param, t_com *com)
{
	char	*oldpwd;
	char	*temp;

	temp = find_env(param, "OLDPWD");
	oldpwd = ft_substr(temp, 1, ft_strlen(temp) - 2);
	if (ft_strlen(oldpwd) == 0)
	{
		printf("cd: OLDPWD not set\n");
		com->error = 1;
	}
	else
		change_dir(param, com, oldpwd);
	free(temp);
	free(oldpwd);
}

static void	change_to_home(t_minishell *param, t_com *com)
{
	char	*path;
	char	*temp;

	temp = find_env(param, "HOME");
	path = ft_substr(temp, 1, ft_strlen(temp) - 2);
	if (ft_strlen(path) == 0)
	{
		printf("cd: No home directory.\n");
		com->error = 1;
	}
	else
		change_dir(param, com, path);
	free(temp);
	free(path);
}

static void	change_dir(t_minishell *param, t_com *com, char *path)
{
	char	*tmp;

	if (!path)
		return ;
	if (chdir(path) != 0)
	{
		printf("Minishell: %s : %s\n", path, strerror(errno));
		com->error = 1;
	}
	else
	{
		tmp = ft_combine_strings(ft_strdup("\""), ft_strdup(param->pwd), \
			ft_strdup("\""));
		if (!(already_exists(param->env, ft_strdup("OLDPWD"), tmp)))
			add_new_env(param->env, ft_strdup("OLDPWD"), tmp);
		set_pwd(param);
	}
}
