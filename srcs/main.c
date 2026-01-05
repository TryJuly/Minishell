/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:58:33 by cbezenco          #+#    #+#             */
/*   Updated: 2026/01/05 13:04:06 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	if (ac != 1)
		return (ft_putstr_fd("Msh: Launch whitout argument\n", 2), 0);
	init_struct(&data, envp);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sighandler);
	signal(SIGSEGV, sigfin);
	read_prompt(&data);
	free_all(&data);
	return (0);
}

void	read_prompt(t_data *data)
{
	char	**array;

	while (1)
	{
		data->input = readline("$> ");
		add_history(data->input);
		if (!ft_strncmp(data->input, "", 1))
		{
			free(data->input);
			continue ;
		}
		if (!ft_strncmp(data->input, "exit", 5))
			break ;
		if (!input_brute(data->input, data))
		{
			new_expand_var(data);
			array = token_array(data->input);
			if (array)
			{
				data->cmd_lst = fill_lst(array);
				exec_cmd(data);
				ft_clear_lst(&data->cmd_lst);
			}
			ft_free_array(&array);
		}
		free(data->input);
	}
	free_all(data);
}

void	sighandler(int signum)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", signum);
	rl_redisplay();
}

void	sigfin(int signum)
{
	(void)signum;
	signum++;
	clear_history();
	exit(130);
}
