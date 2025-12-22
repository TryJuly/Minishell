/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:58:33 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/22 11:53:55 by cbezenco         ###   ########.fr       */
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
	//create_cmd_list(&data);
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

int	check_builtin(t_data *data, t_cmd *cmd)
{
	data->cmd_lst = cmd;

	if (ft_strncmp("echo", data->cmd_lst->args[0], 5) == 0)
		ft_echo(data);
	else if (ft_strncmp("env", data->cmd_lst->args[0], 4) == 0)
		ft_env(data);
	else if (ft_strncmp("pwd", data->cmd_lst->args[0], 4) == 0)
		ft_pwd(data);
	else if (ft_strncmp("cd", data->cmd_lst->args[0], 3) == 0)
		ft_cd(data);
	else if (ft_strncmp("export", data->cmd_lst->args[0], 7) == 0)
		ft_export(data);
	else if (ft_strncmp("unset", data->cmd_lst->args[0], 6) == 0)
		ft_unset(data);
	else if (ft_strncmp("exit", data->cmd_lst->args[0], 5) == 0)
		ft_exit(data);
	else
		return (0);
	return (1);
}

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
			printf("%sCount token = %ld%s\n", YELLOW, token_count(data->input), NC);
			printf("%s####		Command			####%s\n", GREEN, NC);
			printf("%s\n", data->input);
			printf("%s####		Result			####%s\n", GREEN, NC);
			new_expand_var(data);
			array = token_array(data->input);
			data->cmd_lst = fill_lst(array);
			exec_cmd(data);
			ft_free_array(&array);
			free(data->input);
		}
	}
	free(data->input);
}

void	sighandler(int signum)
{
	(void)signum;
	signum++;
	printf("\n$> ");
}

void	sigfin(int signum)
{
	(void)signum;
	signum++;
	clear_history();
	exit(130);
}
