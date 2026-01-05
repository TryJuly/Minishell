/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_v1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:00:22 by strieste          #+#    #+#             */
/*   Updated: 2026/01/05 16:15:32 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	equal_index(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	change_env_var(t_data *data)
{
	int		i;
	int		eq_i;
	int		changed;

	i = 0;
	changed = 0;
	eq_i = equal_index(data->cmd_lst->args[1]);
	while (data->envp[i])
	{
		if (ft_strncmp(data->cmd_lst->args[1], data->envp[i], eq_i) == 0)
		{
			free(data->envp[i]);
			data->envp[i] = ft_strdup(data->cmd_lst->args[1]);
			changed = 1;
		}
		i++;
	}
	return (changed);
}
