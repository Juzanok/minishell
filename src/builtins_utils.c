/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:17:24 by jkarosas          #+#    #+#             */
/*   Updated: 2022/08/11 10:15:34 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_string(char *name, char *content, int len);

int	array_length(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

char	**env_to_str(t_env *env)
{
	char	**str;
	int		len;
	int		i;

	i = 0;
	str = malloc(sizeof(char *) * (envlst_size(env) + 1));
	while (env != NULL)
	{
		len = ft_strlen(env->name) + ft_strlen(env->content) + 2;
		str[i] = get_string(env->name, env->content, len);
		env = env->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

static char	*get_string(char *name, char *content, int len)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = -1;
	str = (char *)malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	while (name[++j])
		str[i++] = name[j];
	if (content)
	{
		str[i] = '=';
		i += 1;
		j = 0;
		while (content && content[j])
			str[i++] = content[j++];
		str[i] = '\0';
	}
	else
		str[i] = '\0';
	return (str);
}

int	envlst_size(t_env *env)
{
	int		length;

	length = 0;
	while (env != NULL)
	{
		env = env->next;
		length++;
	}
	return (length);
}

int	not_valid_env_name(char *name)
{
	int	index;

	index = 0;
	if (!name || !name[index] || \
		!(ft_isalpha(name[index]) || name[index] == '_'))
		return (1);
	index++;
	while (name[index])
	{
		if (ft_isalnum(name[index]) || name[index] == '_')
			index++;
		else
			return (1);
	}
	return (0);
}
