/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:06:12 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/30 14:33:32 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '+')
		i++;
	if (arg[0] == '-')
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
		ft_putstr_fd("too many arguments\n", 2);
		g_exit_status = 1;
		return ;
	}
	if (!check_arg(data->cmd_lst->args[1]))
	{
		ft_putstr_fd("numeric argument required\n", 2);
		g_exit_status = 2;
		exit(g_exit_status);
	}
	g_exit_status = ft_atoi(data->cmd_lst->args[1]);
	clear_history();
	exit(g_exit_status);
}
