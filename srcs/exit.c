/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:06:12 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/12 10:42:30 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
	g_exit_status = ft_atoi(data->cmd_lst->args[1]);
	clear_history();
	exit(g_exit_status);
}
