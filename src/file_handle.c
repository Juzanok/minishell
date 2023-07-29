/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:06:20 by hrings            #+#    #+#             */
/*   Updated: 2022/07/18 11:00:34 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*modify_file_name(t_minishell *param, t_redirect *redirect);

void	redirect_input(t_com *com)
{
	dup2(com->fd_in, STDIN_FILENO);
}

void	redirect_output(t_com *com)
{
	dup2(com->fd_out, STDOUT_FILENO);
}

void	open_input(t_minishell *param, t_com *com, t_redirect *redirect)
{
	if (redirect->redir == HERE_DOC)
		read_here_doc(com, redirect);
	else
	{
		redirect->file = modify_file_name(param, redirect);
		if (ft_strlen(redirect->file) == 0)
		{
			com->error = NOINPUTFILE;
			printf("Minishell: %s : ambiguous redirect\n", redirect->file);
		}
		else if (access(redirect->file, F_OK) == -1)
		{
			com->error = NOINPUTFILE;
			printf("Minishell: %s : %s\n", redirect->file, strerror(errno));
		}
		else if (access(redirect->file, R_OK) == -1)
		{
			com->error = NOREADINPUTFILE;
			printf("Minishell: %s : %s\n", redirect->file, strerror(errno));
		}
		else
			com->fd_in = open(redirect->file, O_RDONLY);
	}
}

void	open_output(t_minishell *param, t_com *com, t_redirect *redirect)
{
	mode_t	mode;
	int		oflag;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	if (redirect->redir == REDIRECT_APPEND)
		oflag = O_WRONLY | O_CREAT | O_APPEND;
	else
		oflag = O_WRONLY | O_CREAT | O_TRUNC;
	redirect->file = modify_file_name(param, redirect);
	if (ft_strlen(redirect->file) == 0)
	{
		com->error = NOINPUTFILE;
		printf("Minishell: %s : ambiguous redirect\n", redirect->file);
	}
	else
		com->fd_out = open(redirect->file, oflag, mode);
	if (com->fd_out < 0)
	{
		com->error = NOEXOUTPUTFILE;
		printf("Minishell: %s : %s\n", redirect->file, strerror(errno));
	}
}

static char	*modify_file_name(t_minishell *param, t_redirect *redirect)
{
	char	*result;
	char	*tmp;

	tmp = expand_env(param, redirect->file);
	result = remove_quote(tmp);
	free(tmp);
	return (result);
}
