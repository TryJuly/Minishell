/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:15:21 by strieste          #+#    #+#             */
/*   Updated: 2025/12/04 15:03:28 by strieste         ###   ########.fr       */
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
# include "libft/libft.h"
# include <stdlib.h>
# include <signal.h>

# define NC "\e[0m"
# define YELLOW "\e[33m"
# define BYELLOW "\e[1;33m"
# define RED "\e[31m"
# define BYRED "\e[1;31m"
# define GREEN "\e[32m"
# define LGREEN "\e[102m"
# define BLUE "\e[34m"

typedef struct s_data
{
	char	*input;
	char	**cmd_brut;
	char	**cmd;
	char	**arg;
	char	**envp;
	char	**path;
	char	**infile;
	char	**outfile;
	int		*fd_infile;
	int		*fd_outfile;
}	t_data;

void	read_prompt(t_data *data);
void	print_tab(char **tab);
void	sighandler(int signum);
void	sigfin(int signum);

/*			Init_struct.c			*/

int		init_struct(t_data *data, char **envp);
int		struct_set(t_data *data);

/*			ft_clean.c				*/

int		ft_free_struct(t_data *data);
void	ft_free_array(char **array);;

int		del_space_cmd_brut(t_data *data);
int		clean_cmd_brut(t_data *data);
int		find_cmd_arg(t_data *data, char *cmd, size_t count_data);
int		infile_open(t_data *data, char *infile, size_t	count_data);
int		outfile_open(t_data *data, char *outfile, size_t count_data);
char	*find_path(char *cmd, char **path);

#endif