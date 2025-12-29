/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:06:12 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/29 14:08:47 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_data *data)
{
	if (data->cmd_lst->args[1] == NULL)
		exit(0);
	if (data->cmd_lst->args[2])
	{
		printf("exit : too many arguments\n");
		g_exit_status = 1;
		return ;
	}
	if (!check_arg(data->cmd_lst->args[1]))
	{
		printf("exit : numeric argument required\n");
		g_exit_status = 2;
		exit(g_exit_status);
	}
	g_exit_status = ft_atoi(data->cmd_lst->args[1]);
	clear_history();
	exit(g_exit_status);
}
