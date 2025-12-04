/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:58:33 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/04 15:30:44 by strieste         ###   ########.fr       */
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
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sighandler);
	signal(SIGSEGV, sigfin);
	read_prompt(&data);
	ft_free_struct(&data);
	return (0);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	read_prompt(t_data *data)
{
	size_t	count;

	count = 0;
	while (1)
	{
		data->input = readline("$> ");
		if (ft_strncmp(data->input, "", 1) == 0)
			continue ;
		else if (ft_strncmp(data->input, "exit", 5) == 0)
			break ;
		data->cmd_brut = ft_split(data->input, '|');
		printf("%sCmd brut%s\n", GREEN, NC);
		print_tab(data->cmd_brut);
		clean_cmd_brut(data);
		printf("%sCmd brut Clean%s\n", GREEN, NC);
		print_tab(data->cmd_brut);
		add_history(data->input);
		printf("%sSplit under cmd%s\n", GREEN, NC);
		// print_tab(data->path);
		while (data->cmd_brut[count])
		{
			find_cmd_arg(data, data->cmd_brut[count], count);
			count++;
		}
		print_tab(data->cmd);
		print_tab(data->arg);
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
