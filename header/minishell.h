/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:57:13 by hrings            #+#    #+#             */
/*   Updated: 2022/08/11 11:07:43 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>

# define REDIRECT_OVER 1
# define REDIRECT_APPEND 2
# define REDIRECT_INPUT 3
# define HERE_DOC 4
# define PROMPT "Minishell$ "

# define NOINPUTFILE 1
# define NOREADINPUTFILE 2
# define NOEXOUTPUTFILE 3

# define PARSEPIPE 1
# define REDIRECTERROR 2

typedef struct s_words
{
	char			*oldword;
	char			*newword;
	int				count;
	struct s_words	*next;
}				t_words;

typedef struct s_checker
{
	int	index;
	int	result;
}	t_checker;

typedef struct s_com	t_com;

typedef struct s_input
{
	char			*line;
	struct s_input	*next;
}			t_input;

typedef struct s_redirect
{
	int					redir;
	char				*file;
	char				*delim;
	int					doc_pipe[2];
	struct s_redirect	*next;
}			t_redirect;

typedef struct s_coms
{
	t_com			*com;
	struct s_coms	*next;
}			t_coms;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	t_env	*env;
	int		exit_code;
	char	**path;
	t_input	*input;
	t_coms	*coms;
	int		*pipes;
	int		num_com;
	char	**commands;
	char	*pwd;
	char	*user;
}			t_minishell;

typedef struct s_com
{
	int			red_input;
	int			red_output;
	int			fd_in;
	int			fd_out;
	t_redirect	*redirect;
	char		*com_line;
	char		**arg;
	char		*path;
	int			error;
	int			index;
}				t_com;

typedef struct s_index
{
	int	index;
	int	index2;
}				t_index;

//main
void	initpath(t_minishell *param);
void	parser(t_minishell *param, char *line);
t_input	*ft_listnew(char *line);
void	list_push(t_minishell *param, char *line);
void	print_list(t_minishell *param);
void	free_list(t_minishell *param);
//run_commands.c
void	run_commands(t_minishell *param);
void	multi_line_com(t_minishell *param, char *line);
int		ft_input_size(t_input *lst);
//run_pipes
void	run_pipes(t_minishell *param);
void	runshellcmd(t_minishell *param, t_com *com);
void	run_single_com(t_minishell *param);
//parse_com_line
t_com	*parse_com_line(char *line);
//parse_redirect
int		parse_redirect(t_com *result, char *line, int index);
//utilities
int		skip_whitespace(char *line, int index);
int		is_buildin(char *command);
int		find_end_quote(char *line, int index);
int		not_redirection_end(char c);
char	**ft_split_pipex(char const *s, char c);
//file_handle
void	redirect_input(t_com *com);
void	redirect_output(t_com *com);
void	open_input(t_minishell *param, t_com *com, t_redirect *redirect);
void	open_output(t_minishell *param, t_com *com, t_redirect *redirect);
//child
void	child(t_minishell *param, t_com *com);
//handle_pipes
void	creat_pipes(t_minishell *param);
void	close_pipes(t_minishell *param);
void	prepare_pipes(t_minishell *param);
//pipe_util
char	*joinpath(char *directory, char *command);
char	*getpath(t_minishell *param, t_com *com, char *command);
int		ft_strfind(char *str, char c);
//redirection
void	redirect(t_minishell *param, t_com *com);
void	open_redirections(t_minishell *param, t_com *com);
//list_coms
void	free_list_com(t_minishell *param);
void	list_coms_push(t_minishell *param, t_com	*com);
//here_doc
void	read_here_doc(t_com *com, t_redirect *redirect);
//list_redirect
void	list_push_redirect(t_com *com, char *line, int redir, char *delim);
void	free_list_redirect(t_com *com);
//error_handling
void	error_parser(t_minishell *param, int error_num, char c);
void	error_handler_pip(t_minishell *param);
void	error_export(t_com *com, int i, char *name);
void	error_unset(t_com *com, int i);
//signal
void	handler_sig(int n);
void	handler_sig_here(int n);
//quote_checker
int		quote_checker(char *line);
//parse_utilities
int		next_d_quote(char *line, int index, int i);
int		next_s_quote(char *line, int index, int i);
int		index_add(char *line, int index, int i);
int		not_valid_env_name(char *name);
//builtins
void	ft_cd(t_minishell *param, t_com *com);
void	ft_unset(t_minishell *param, t_com *com);
void	ft_export(t_minishell *param, t_com *com);
void	ft_echo(t_com *com);
void	ft_env(t_env *env, t_com *com);
void	ft_pwd(t_minishell *param, t_com *com);
int		array_length(char **array);
int		ft_strcmp(const char *s1, const char *s2);
void	free_array(char **array);
char	**env_to_str(t_env *env);
int		envlst_size(t_env *env);
void	add_new_env(t_env *env, char *name, char *content);
int		already_exists(t_env *env, char *name, char *content);
int		env_exists(t_env *env, char *name);
char	*ft_combine_strings(char *str1, char *str2, char *str3);
void	export_add_oldpwd(t_minishell *param);
//expand_env
char	*expand_env(t_minishell *param, char *line);
//replace_word
char	*replace_word(char *line, t_words *words);
//env_list
void	init_env(t_minishell *param, char **envp);
char	*get_name(char *str);
char	*get_content(char *str);
char	*find_env(t_minishell *param, char *oldword);
void	free_env(t_minishell *param);
//ft_exit.c
void	ft_exit(t_minishell *param, t_com *com);
//cleanup.c
int		full_clean_up(t_minishell *param);
int		full_clean_up_com(t_minishell *param, t_com *com);
void	clean_up_com(t_com *com);
//quote_handling
void	quote_handling(t_com *com);
char	*remove_quote(char *line);
//list_words
void	list_word_add(t_minishell *param, t_words *listwords, char *word);
int		find_new_line_len(char *line, t_words *words);
void	free_words(t_words *words);
//replace_word_util
void	add_new_word(char *result, char *new, int index);
t_words	*is_in_line(char *line, t_words *words, int i);
int		var_start(char c);
int		var_start_in_quote(char c);
//prompt
char	*display_prompt(t_minishell *param);
void	set_pwd(t_minishell *param);
#endif
