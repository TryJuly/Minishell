/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:06:12 by cbezenco          #+#    #+#             */
/*   Updated: 2026/02/03 14:22:33 by cbezenco         ###   ########.fr       */
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
	{
		free_all(data);
		exit(0);
	}
	if (data->cmd_lst->args[2])
	{
		ft_putstr_fd("Msh: Too many arguments\n", 2);
		exit_status(1, 1);
		return ;
	}
	if (!check_arg(data->cmd_lst->args[1]))
	{
		ft_putstr_fd("Msh: Numeric argument required\n", 2);
		exit_status(255, 1);
		free_all(data);
		exit(exit_status(0, 0));
	}
	exit_status(ft_atoi(data->cmd_lst->args[1]), 1);
	free_all(data);
	exit(exit_status(0, 0));
}
