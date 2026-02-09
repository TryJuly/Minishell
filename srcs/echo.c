/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:41:25 by cbezenco          #+#    #+#             */
/*   Updated: 2026/02/03 14:18:49 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	is_n_option(char *str);

void	ft_echo(t_data *data)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = 0;
	while (data->cmd_lst->args[i] && is_n_option(data->cmd_lst->args[i]))
	{
		n_option = 1;
		i++;
	}
	while (data->cmd_lst->args[i])
	{
		ft_putstr_fd(data->cmd_lst->args[i], 1);
		if (data->cmd_lst->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_option)
		write(1, "\n", 1);
	exit_status(0, 1);
}

static int	is_n_option(char *str)
{
	int	i;

	if (str[0] != '-' || str[1] != 'n')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
