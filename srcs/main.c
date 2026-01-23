/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:58:33 by cbezenco          #+#    #+#             */
/*   Updated: 2026/01/23 11:07:57 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int g_exit_status = 0;

void    read_prompt(t_data *data)
{
    char    **array;

    while (1)
    {
        data->input = readline("$> ");
        if (!data->input) break;
        if (data->input[0] == '\0')
        {
            free(data->input);
            continue ;
        }
        add_history(data->input);
        if (quote_check_input(data->input) == 1)
		{
			free(data->input);
			continue ;
		}
		array = token_array(data->input);
		if (array)
		{
			if (syntax_check(array) != 0)
			{
				g_exit_status = 2;
				ft_free_array(&array);
				continue ;
			}
			if (heredoc_check(array, data) == -1)
			{
				ft_free_array(&array);
				free(data->input);
				continue ;
			}
			data->cmd_lst = fill_lst(array);
			ft_free_array(&array);
			if (!data->cmd_lst)
			{
				free_all(data);
				exit(1);
			}
			replace_var_value(data);
			exec_cmd(data);
			ft_clear_lst(&data->cmd_lst);
		}
        free(data->input);
    }
}

int main(int ac, char **av, char **envp)
{
    t_data  data;

    (void)av;
    if (ac != 1)
    {
        ft_putstr_fd("Msh: Launch without argument\n", 2);
        return (1);
    }
    init_struct(&data, envp);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, sighandler);
    read_prompt(&data);
    free_all(&data);
    clear_history();
    return (g_exit_status);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_data	data;

// 	(void)av;
// 	if (ac != 1)
// 		return (ft_putstr_fd("Msh: Launch whitout argument\n", 2), 0);
// 	init_struct(&data, envp);
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGINT, sighandler);
// 	// signal(SIGSEGV, sigfin);
// 	read_prompt(&data);
// 	free_all(&data);
// 	return (0);
// }

// void	read_prompt(t_data *data)
// {
// 	char	**array;

// 	while (1)
// 	{
// 		data->input = readline("$> ");
// 		add_history(data->input);
// 		if (!ft_strncmp(data->input, "", 1))
// 		{
// 			free(data->input);
// 			continue ;
// 		}
// 		if (!input_brute(data->input, data))
// 		{
// 			array = token_array(data->input);
// 			if (array)
// 			{
// 				if (heredoc_check(array, data) == -1)
// 				{
// 					ft_free_array(&array);
// 					free(data->input);
// 					continue ;
// 				}
// 				replace_var_value(&array, data);
// 				data->cmd_lst = fill_lst(array);
// 				exec_cmd(data);
// 				ft_clear_lst(&data->cmd_lst);
// 			}
// 			ft_free_array(&array);
// 		}
// 		free(data->input);
// 	}
// 	free_all(data);
// }

void	sighandler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	// rl_replace_line("", signum);
	rl_redisplay();
}

void	sigfin(int signum)
{
	(void)signum;
	signum++;
	clear_history();
	exit(130);
}
