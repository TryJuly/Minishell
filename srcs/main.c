/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:58:33 by cbezenco          #+#    #+#             */
/*   Updated: 2026/02/03 14:34:42 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	handle_token(char **array, t_data *data);

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	if (ac != 1)
	{
		ft_putstr_fd("Msh: Launch without argument\n", 2);
		return (1);
	}
	init_struct(&data, envp);
	read_prompt(&data);
	free_all(&data);
	clear_history();
	return (exit_status(0, 0));
}

void	prompt_start(t_data *data)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sighandler);
	data->input = readline("$> ");
}

int	check_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	read_prompt(t_data *data)
{
	char	**array;

	while (1)
	{
		prompt_start(data);
		if (!data->input)
			break ;
		if (data->input[0] == '\0' || !check_spaces(data->input))
		{
			free(data->input);
			continue ;
		}
		add_history(data->input);
		if (quote_check_input(data->input) == 1)
		{
			exit_status(2, 1);
			free(data->input);
			continue ;
		}
		array = token_array(data->input);
		free(data->input);
		if (array)
			handle_token(array, data);
	}
}

static int	handle_token(char **array, t_data *data)
{
	signal(SIGQUIT, sighandler_v4);
	signal(SIGINT, sigfin);
	if (syntax_check(array) != 0)
	{
		exit_status(2, 1);
		return (ft_free_array(&array), 1);
	}
	if (heredoc_check(array, data) == -1)
		return (ft_free_array(&array), 1);
	signal(SIGINT, sigfin);
	data->cmd_lst = fill_lst(array, 0, NULL);
	ft_free_array(&array);
	if (!data->cmd_lst)
	{
		free_all(data);
		exit(1);
	}
	replace_var_value(data);
	exec_cmd(data);
	ft_clear_lst(&data->cmd_lst);
	return (0);
}
