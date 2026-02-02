/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:41:25 by cbezenco          #+#    #+#             */
/*   Updated: 2026/01/29 11:22:28 by strieste         ###   ########.fr       */
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
	g_exit_status = 0;
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
