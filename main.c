/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:58:33 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/09 13:30:52 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	g_exit_status;

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
	return (0);
}
/*debug*/

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

void	check_builtin(t_data *data)
{
	char	**array;

	array = ft_split(data->cmd_brut[0], ' ');
	data->arg = array;
	expand_var(data);
	data->arg += 1;
	if (ft_strncmp("echo", array[0], 5) == 0)
		ft_echo(data);
	else if (ft_strncmp("env", array[0], 4) == 0)
		ft_env(data);
	else if (ft_strncmp("pwd", array[0], 4) == 0)
		ft_pwd(data);
	else if (ft_strncmp("cd", array[0], 3) == 0)
		ft_cd(data);
	else if (ft_strncmp("export", array[0], 7) == 0)
		ft_export(data);
	else if (ft_strncmp("unset", array[0], 6) == 0)
		ft_unset(data);
	else if (ft_strncmp("exit", array[0], 5) == 0)
		ft_exit(data);
}

void	read_prompt(t_data *data)
{
	// size_t	count;

	// count = 0;
	while (1)
	{
		data->input = readline("$> ");
		if (ft_strncmp(data->input, "", 1) == 0)
			continue ;
		data->cmd_brut = ft_split(data->input, '|');
		printf("%sCmd brut%s\n", GREEN, NC);
		print_tab(data->cmd_brut);
		clean_cmd_brut(data);
		printf("%sCmd brut Clean%s\n", GREEN, NC);
		print_tab(data->cmd_brut);
		add_history(data->input);
		printf("%sSplit under cmd%s\n", GREEN, NC);
		// print_tab(data->path);
		// while (data->cmd_brut[count])
		// {
		// 	find_cmd_arg(data, data->cmd_brut[count], count);
		// 	count++;
		// }
		check_builtin(data);
		// print_tab(data->cmd);
		// print_tab(data->arg);
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
	exit(0);
}
