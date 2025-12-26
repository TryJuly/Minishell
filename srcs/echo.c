/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:41:25 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/26 12:20:26 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_echo_n(t_data *data)
{
	int	i;

	i = 1;
	if (!data->cmd_lst->args[i + 1])
		return ;
	while (data->cmd_lst->args[i + 1])
	{
		printf("%s", data->cmd_lst->args[i + 1]);
		if (data->cmd_lst->args[i + 2])
			printf(" ");
		i++;
	}
}

void	ft_echo(t_data *data)
{
	int	i;

	i = 0;
	if (!data->cmd_lst->args[1])
	{
		printf("\n");
		return ;
	}
	if (ft_strncmp(data->cmd_lst->args[1], "-n", 2) == 0)
	{
		ft_echo_n(data);
		return ;
	}
	while (data->cmd_lst->args[i + 1])
	{
		printf("%s", data->cmd_lst->args[i + 1]);
		if (data->cmd_lst->args[i + 2])
			printf(" ");
		i++;
	}
	printf("\n");
}
