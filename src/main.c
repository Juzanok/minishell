/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:58:14 by hrings            #+#    #+#             */
/*   Updated: 2022/08/11 11:20:21 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	run_on_line(t_minishell *param, char *line);
static void	init_param(t_minishell *param, char **envp);
static void	init_pwd_user(t_minishell *param);

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	*param;
	char		*prompt;

	if (argc != 1 || argv[1])
		exit(1);
	param = (t_minishell *)malloc(sizeof(t_minishell));
	if (!param)
		return (1);
	init_param(param, envp);
	signal(SIGINT, handler_sig);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		prompt = display_prompt(param);
		line = readline(prompt);
		free(prompt);
		if (!line)
			break ;
		run_on_line(param, line);
	}
	free_env(param);
	printf("\n");
	return (full_clean_up(param));
}

static void	run_on_line(t_minishell *param, char *line)
{
	add_history(line);
	if (quote_checker(line))
		multi_line_com(param, line);
	free(line);
}

static void	init_param(t_minishell *param, char **envp)
{
	param->input = NULL;
	param->coms = NULL;
	param->pipes = NULL;
	param->path = NULL;
	param->commands = NULL;
	param->exit_code = 0;
	init_env(param, envp);
	init_pwd_user(param);
}

void	initpath(t_minishell *param)
{
	char	*result;
	int		index;

	index = 0;
	if (param->path)
	{
		while (param->path[index])
			free(param->path[index++]);
		free(param->path);
	}
	result = find_env(param, "PATH");
	if (ft_strlen(result))
		param->path = ft_split(result, ':');
	else
		param->path = NULL;
	free(result);
}

static void	init_pwd_user(t_minishell *param)
{
	char	*tmp;

	tmp = find_env(param, "USER");
	param->user = remove_quote(tmp);
	free(tmp);
	tmp = find_env(param, "PWD");
	param->pwd = remove_quote(tmp);
	free(tmp);
	if (!param->pwd || (ft_strlen(param->pwd) == 0))
		set_pwd(param);
}
