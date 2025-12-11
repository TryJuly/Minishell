/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:58:33 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/11 14:23:14 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	g_exit_status = 0;

void	create_cmd_list(t_data *data)
{
	t_cmd	*new_cmd_lst;

	new_cmd_lst = malloc(sizeof(t_cmd));
	data->cmd_lst = new_cmd_lst;
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	init_struct(&data, envp);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sighandler);
	signal(SIGSEGV, sigfin);
	create_cmd_list(&data);
	read_prompt(&data);
	ft_free_array(&data.path);
	ft_free_array(&data.envp);
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

void	check_builtin(t_data *data, char **array)
{
	data->cmd_lst->args = array;
	//data->cmd_lst->args += 1;
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
	char	**array;

	while (1)
	{
		data->input = readline("$> ");
		if (!ft_strncmp(data->input, "", 1))
			continue ;
		printf("%s###############	Print	###############%s\n", GREEN, NC);
		printf("%sCount token = %ld%s\n", YELLOW, token_count(data->input), NC);
		printf("%s\n", data->input);
		printf("%s###############	Print Tab	###############%s\n", GREEN, NC);
		new_expand_var(data);
		array = token_array(data->input);
		print_tab(array);
		check_builtin(data, array);
		// if (validator(array))
		// 	printf("%sError validator%s\n", RED, NC);
		//ft_free_array(&array);
		//free(data->input);
	}
	free(data->input);
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
