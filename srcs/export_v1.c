/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_v1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:00:22 by strieste          #+#    #+#             */
/*   Updated: 2026/01/23 12:47:12 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	equal_index(char *str);
//		USE
int	change_env_var(t_data *data, int index)
{
	int		i;
	int		eq_i;
	int		changed;

	i = 0;
	changed = 0;
	eq_i = equal_index(data->cmd_lst->args[index]);
	while (data->envp[i])
	{
		if (!ft_strncmp(data->cmd_lst->args[index], data->envp[i], eq_i) && data->envp[i][eq_i] == '=')
		{
			free(data->envp[i]);
			data->envp[i] = ft_strdup(data->cmd_lst->args[index]);
			changed = 1;
		}
		i++;
	}
	return (changed);
}

static int	equal_index(char *str)
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
