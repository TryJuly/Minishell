/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:58:33 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/26 12:28:05 by strieste         ###   ########.fr       */
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

// void	create_cmd_list(t_data *data)
// {
// 	t_cmd	*new_cmd_lst;

// 	new_cmd_lst = malloc(sizeof(t_cmd));
// 	data->cmd_lst = new_cmd_lst;
// }
/*debug*/

// void	print_tab(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// }

void	read_prompt(t_data *data)
{
	char	**array;

	while (1)
	{
		data->input = readline("$> ");
		if (!ft_strncmp(data->input, "", 1))
			continue ;
		if (!ft_strncmp(data->input, "exit", 5))
			break ;
		if (!input_brute(data->input, data))
		{
			new_expand_var(data);
			array = token_array(data->input);
			data->cmd_lst = fill_lst(array);
			exec_cmd(data);
			free_classic(array);
		}
		add_history(data->input);
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
