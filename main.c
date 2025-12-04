/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:58:33 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/04 08:58:15 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	
	(void)ac;
	(void)av;
	struct_set(&data);
	init_struct(&data, envp);
	ft_free_struct(&data);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sighandler);
	signal(SIGSEGV, sigfin);
	read_prompt();
	return (0);
}

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

void	sighandler(int signum)
{
	signum++;
	printf("\n$> ");
}

void	sigfin(int signum)
{
	signum++;
	rl_clear_history();
	exit(1);
}
