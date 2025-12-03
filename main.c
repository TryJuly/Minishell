/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:58:33 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/03 14:48:53 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include "libft/libft.h"
#include <stdlib.h>
#include <signal.h>

void	sighandler(int);

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s ", tab[i]);
		i++;
	}
	printf("\n");
}

void	read_prompt(void)
{
	char	*line;
	char	**tab_cmd;

	line = "";
	while (1)
	{
		line = readline("$> ");
		if (ft_strncmp(line, "", 1) == 0)
			continue ;
		else if (ft_strncmp(line, "exit", 5) == 0)
			break ;
		else
		{
			tab_cmd = ft_split(line, ' ');
			print_tab(tab_cmd);
			add_history(line);
		}
	}
}

int	main(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, sighandler);
	read_prompt();
	return (0);
}

void	sighandler(int signum)
{
	signum++;
	read_prompt();
}
