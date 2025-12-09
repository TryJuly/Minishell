/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:41:25 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/08 11:43:05 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_echo_n(t_data *data)
{
	int	i;

	i = 0;
	if (!data->arg[i])
		return ;
	while (data->arg[i])
	{
		printf("%s", data->arg[i]);
		if (data->arg[i + 1])
			printf(" ");
		i++;
	}
}


void	ft_echo(t_data *data)
{
	int	i;

	i = 0;
	if (!data->arg[0])
	{
		printf("\n");
		return ;
	}
	if (ft_strncmp(data->arg[0], "-n", 2) == 0)
	{
		data->arg += 1;
		ft_echo_n(data);
		return ;
	}
	while (data->arg[i])
	{
		printf("%s", data->arg[i]);
		if (data->arg[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}
