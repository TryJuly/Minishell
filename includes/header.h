/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:15:21 by strieste          #+#    #+#             */
/*   Updated: 2026/02/03 14:30:00 by cbezenco         ###   ########.fr       */
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
void	sigheredoc(int signum);
void	sighandler(int signum);
void	sighandler_v4(int signum);
void	read_prompt(t_data *data);
int		exit_status(int status, int booly);

/*			Check_input				*/

int		syntax_check(char **token);
int		quote_check_input(char *str);

/*			Init_struct.c			*/

int		init_struct(t_data *data, char **envp);

/*			Token Parsing + utils	*/

char	*dup_char(char c);
size_t	token_count(char *s);
char	**token_array(char *s);
char	*remove_quote(char *str);
int		op_check(char c, char next);
int		copy_word(char *s, char **str);
int		search_occur(char *str, char c);
int		ending_quote(char *s, char quote);
char	*get_env_value(char *var_name, t_data *data);

/*			Fill lst + tools			*/

int		is_redir(char *str);
int		lst_size(t_cmd *cmd);
int		get_redir_type(char *redir);
int		find_path(char **cmd, char **path);
void	add_back_lst(t_cmd **cmd, t_cmd *new);
t_cmd	*fill_lst(char **array, size_t len, t_cmd *lst);

/*			Built-ins functions		*/

void	ft_cd(t_data *data);
void	ft_env(t_data *data);
void	ft_pwd(t_data *data);
void	ft_echo(t_data *data);
void	ft_exit(t_data *data);
int		ft_unset(t_data *data);
void	ft_export(t_data *data);

/*			Expand environment variables	*/

int		replace_var_value(t_data *data);
char	*expand_token(char *str, t_data *data);
int		change_env_var(t_data *data, int index);

/*			Execve.c				*/

int		exec_cmd(t_data *data);
int		check_builtin(t_data *data, t_cmd *cmd);
int		get_cmdpath(t_data **data, char **envp);

/*			redir.c					*/

int		redir_file(int *in, int *out, t_redir *redir);

/*			Tool.c					*/

void	init_pipe(int *pipe);
int		arr_size(char **arr);
void	set_path(t_data *data, t_cmd **cmd);
t_cmd	*malloc_args(char **array, size_t len);
int		close_dup_fd(int *in, int *out, int pipe_fd[2], int *prev_fd);

/*			ft_clean.c				*/

void	error_malloc(void);
void	free_all(t_data *data);
void	ft_clear_lst(t_cmd **lst);
void	free_classic(char **envp);
int		ft_free_array(char ***array);

/*			heredoc.c				*/

int		heredoc_check(char **array, t_data *data);

#endif