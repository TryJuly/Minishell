/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:15:21 by strieste          #+#    #+#             */
/*   Updated: 2026/01/05 11:05:45 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <termios.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

# define NC "\e[0m"
# define YELLOW "\e[33m"
# define BYELLOW "\e[1;33m"
# define RED "\e[31m"
# define BYRED "\e[1;31m"
# define GREEN "\e[32m"
# define LGREEN "\e[102m"
# define BLUE "\e[34m"

# define R_IN 1
# define R_OUT 2
# define R_HEREDOC 3
# define R_APPEND 4

extern int				g_exit_status;
typedef struct s_cmd	t_cmd;
typedef struct s_redir	t_redir;

typedef struct s_data
{
	t_cmd	*cmd_lst;
	char	*input;
	char	**envp;
	char	**path;
	int		heredoc;
}	t_data;

typedef struct s_cmd
{
	char			**args;
	struct s_redir	*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

void	sigfin(int signum);
void	sighandler(int signum);
void	read_prompt(t_data *data);

/*			Check_input				*/

int		is_out_check(char *str);
int		input_brute(char *str, t_data *data);
int		find_heredoc(char *str, t_data *data);

/*			Init_struct.c			*/

int		init_struct(t_data *data, char **envp);

/*			Token Parsing + utils	*/

char	*dup_char(char c);
size_t	token_count(char *s);
char	**token_array(char *s);
int		op_check(char c, char next);
int		tokenizer(char *s, char **array);
int		ending_quote(char *s, char quote);
int		operator(char c, char next, char **str);

/*			Fill lst + tools			*/

int		is_redir(char *str);
int		lst_size(t_cmd *cmd);
int		lst_size(t_cmd *cmd);
t_cmd	*lst_last(t_cmd *cmd);
t_cmd	*fill_lst(char **array);
int		get_redir_type(char *redir);
int		find_path_1(char **cmd, char **path);
void	add_back_lst(t_cmd **cmd, t_cmd *new);

/*			export.c (pot. utils.c)	*/

int		arr_size(char **arr);

/*			Built-ins functions		*/

void	ft_cd(t_data *data);
void	ft_env(t_data *data);
void	ft_pwd(t_data *data);
void	ft_echo(t_data *data);
void	ft_exit(t_data *data);
void	ft_unset(t_data *data);
void	ft_echo_n(t_data *data);
void	ft_export(t_data *data);

/*			Expand environment variables	*/

char	*ft_unsplit(char **tab);
int		count_dollars(char *str);
int		no_dollars(char	*str);
void	new_expand_var(t_data *data);
void	heredoc(char *input, t_data *data);
char	*expand_line(char *line, t_data *data);
char	**ft_split_dollars(char *input, int dollars);
char	*expand_var_value(char *new_str, t_data *data);
char	*expand_command_value(char *new_str, t_data *data);

/*			Execve.c				*/

int		exec_cmd(t_data *data);

/*			redir.c					*/

int		redir_file(int *in, int *out, t_redir *redir);

/*			Tool.c					*/

void	init_pipe(int *pipe);
int		skip_space(char *str);
int		count_args(char **array, int len);
void	set_path(t_data *data, t_cmd **cmd);
t_cmd	*malloc_args(char **array, size_t len);
int		close_dup_fd(int *in, int *out, int pipe_fd[2], int *prev_fd);

/*			ft_clean.c				*/

void	free_all(t_data *data);
void	ft_clear_lst(t_cmd **lst);
void	free_classic(char **envp);
int		ft_free_array(char ***array);

/*			???						*/
int		check_builtin(t_data *data, t_cmd *cmd);
int		get_cmdpath(t_data **data, char **envp);
// void	print_lst(t_cmd *lst);

#endif