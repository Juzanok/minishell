/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:34:19 by hrings            #+#    #+#             */
/*   Updated: 2022/08/10 09:50:50 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	childs(t_minishell *param, t_com	*com);
static void	split_process(t_minishell *param);
static void	wait_and_clean(t_minishell *param, pid_t *pid);

void	run_pipes(t_minishell *param)
{
	creat_pipes(param);
	prepare_pipes(param);
	split_process(param);
	free_list_com(param);
	free_list(param);
	free(param->pipes);
	param->pipes = NULL;
}

static void	split_process(t_minishell *param)
{
	pid_t	*pid;
	t_coms	*current;
	int		index;

	current = param->coms;
	pid = (pid_t *)malloc(sizeof(pid_t) * param->num_com);
	if (!pid)
		exit (1);
	index = 0;
	while (current)
	{
		pid[index] = fork();
		if (pid[index++] == 0)
		{
			free(pid);
			childs(param, current->com);
		}
		current = current->next;
	}
	wait_and_clean(param, pid);
}

static void	childs(t_minishell *param, t_com	*com)
{
	if (!com->error && com->arg && com->arg[0])
	{
		redirect(param, com);
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
			runshellcmd(param, com);
	}
	exit(full_clean_up_com(param, com));
}

void	runshellcmd(t_minishell *param, t_com *com)
{
	char	**env;

	env = env_to_str(param->env);
	execve(com->path, com->arg, env);
	printf("Minishell: %s : %s\n", com->path, strerror(errno));
	free_array(env);
	com->error = errno;
	exit(full_clean_up_com(param, com));
}

static void	wait_and_clean(t_minishell *param, pid_t *pid)
{
	int	index;
	int	status;

	close_pipes(param);
	index = 0;
	signal(SIGINT, SIG_IGN);
	while (index < param->num_com)
		waitpid(pid[index++], &status, WUNTRACED);
	signal(SIGINT, handler_sig);
	free(pid);
	param->exit_code = WEXITSTATUS(status);
}
