/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:06:12 by cbezenco          #+#    #+#             */
/*   Updated: 2026/01/22 17:22:35 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '+' || arg[0] == '-')
		i++;
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
		ft_putstr_fd("Msh: Too many arguments\n", 2);
		g_exit_status = 1;
		return ;
	}
	if (!check_arg(data->cmd_lst->args[1]))
	{
		ft_putstr_fd("Msh: Numeric argument required\n", 2);
		g_exit_status = 255;
		exit(g_exit_status);
	}
	g_exit_status = ft_atoi(data->cmd_lst->args[1]);
	// rl_clear_history();
	exit(g_exit_status);
}
