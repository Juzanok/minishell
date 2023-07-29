/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:28:39 by hrings            #+#    #+#             */
/*   Updated: 2022/08/03 10:22:35 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	read_input(t_redirect *redirect);
static void	wait_here_doc(t_com *com, pid_t pid);

void	read_here_doc(t_com *com, t_redirect *redirect)
{
	pid_t	pid;

	if (pipe(redirect->doc_pipe) < 0)
		exit(1);
	com->fd_in = redirect->doc_pipe[0];
	pid = fork();
	if (pid == 0)
		read_input(redirect);
	else
		wait_here_doc(com, pid);
	if (redirect->delim)
		free(redirect->delim);
	close(redirect->doc_pipe[1]);
}

static void	read_input(t_redirect *redirect)
{
	char	*line;

	signal(SIGINT, handler_sig_here);
	while (1)
	{
		if (write(1, "heredoc: ", 9) == -1)
			exit(1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(redirect->delim, line, ft_strlen(redirect->delim)))
		{
			free(line);
			break ;
		}
		if (write(redirect->doc_pipe[1], line, ft_strlen(line)) == -1)
			printf("error pipe");
		free(line);
	}
	exit(0);
}

static void	wait_here_doc(t_com *com, pid_t pid)
{
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &com->error, 0);
	signal(SIGINT, handler_sig);
}
