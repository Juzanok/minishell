/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_single_com.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 09:02:36 by hrings            #+#    #+#             */
/*   Updated: 2022/08/10 09:50:57 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	run_com(t_minishell *param, t_com *com);
static void	find_com_type(t_minishell *param, t_com *com);
static void	prepare_and_run(t_minishell *param, t_com *com);

void	run_single_com(t_minishell *param)
{
	t_com	*com;

	com = parse_com_line(param->input->line);
	if (com->error)
	{
		param->exit_code = com->error;
		clean_up_com(com);
	}
	else
		prepare_and_run(param, com);
}

static void	run_com(t_minishell *param, t_com *com)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		child(param, com);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, WUNTRACED);
	signal(SIGINT, handler_sig);
	com->error = WEXITSTATUS(status);
}

static void	find_com_type(t_minishell *param, t_com *com)
{
	if (ft_strcmp(com->arg[0], "cd") == 0)
		ft_cd(param, com);
	else if (ft_strcmp(com->arg[0], "export") == 0)
		ft_export(param, com);
	else if (ft_strcmp(com->arg[0], "unset") == 0)
		ft_unset(param, com);
	else if (ft_strcmp(com->arg[0], "echo") == 0)
		ft_echo(com);
	else if (ft_strcmp(com->arg[0], "env") == 0)
		ft_env(param->env, com);
	else if (ft_strcmp(com->arg[0], "pwd") == 0)
		ft_pwd(param, com);
	else if (ft_strcmp(com->arg[0], "exit") == 0)
		ft_exit(param, com);
	else
	{
		initpath(param);
		com->path = getpath(param, com, com->arg[0]);
		run_com(param, com);
	}
	param->exit_code = com->error;
}

static void	prepare_and_run(t_minishell *param, t_com *com)
{
	list_coms_push(param, com);
	open_redirections(param, com);
	if (com->com_line != NULL)
	{
		com->com_line = expand_env(param, com->com_line);
		com->arg = ft_split_pipex(com->com_line, ' ');
		quote_handling(com);
	}
	if (!com->error && com->arg && com->arg[0])
		find_com_type(param, com);
	free_list_com(param);
}
