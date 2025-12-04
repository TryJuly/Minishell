/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:15:21 by strieste          #+#    #+#             */
/*   Updated: 2025/12/04 08:42:38 by strieste         ###   ########.fr       */
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

typedef struct s_data
{
	char	**cmd;
	char	**envp;
	char	**path;
	int		*redir;
}	t_data;

void	read_prompt(void);
void	print_tab(char **tab);
void	sighandler(int signum);
void	sigfin(int signum);

/*			Init_struct.c			*/

int		init_struct(t_data *data, char **envp);
int		struct_set(t_data *data);

/*			ft_clean.c				*/

int		ft_free_struct(t_data *data);
void	ft_free_array(char **array);;

#endif