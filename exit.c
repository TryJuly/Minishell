/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:06:12 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/09 10:21:53 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_exit(t_data *data)
{
	if (data->arg[0] == NULL)
		exit(0);
	if (data->arg[1])
	{
		printf("exit : too many arguments\n");
		g_exit_status = 1;
		return ;
	}
	g_exit_status = ft_atoi(data->arg[0]);
	rl_clear_history();
	exit(g_exit_status);
}
