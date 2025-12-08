/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:15:21 by strieste          #+#    #+#             */
/*   Updated: 2025/12/08 14:06:08 by strieste         ###   ########.fr       */
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

typedef struct s_cmd t_cmd;

typedef struct s_data
{
	t_cmd	*cmd_lst;
	char	*input;
	char	**env;
	char	**path;
}	t_data;

typedef struct s_cmd
{
	int				index;
	char			*cmd;
	char			**args;
	char			*in;
	char			*out;
	int				append;
	int				heredoc;
	char			*pass_w;
	struct s_cmd	*next;
}	t_cmd;

void	read_prompt(t_data *data);
void	print_tab(char **tab);
void	sighandler(int signum);
void	sigfin(int signum);

/*			Init_struct.c			*/

int		init_struct(t_data *data, char **envp);

/*			ft_clean.c				*/

int		ft_free_array(char ***array);

/*			Token_count.c			*/
size_t	token_count(char *s);
int		op_check(char c, char next);;

/*			Tokenizer.c				*/

int	tokenizer(char *s, char **array);
char	**token_array(char *s);


#endif