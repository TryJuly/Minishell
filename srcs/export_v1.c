/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_v1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:00:22 by strieste          #+#    #+#             */
/*   Updated: 2026/01/23 17:19:23 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	equal_index(char *str);

int	change_env_var(t_data *data, int index)
{
	int		i;
	int		eq_i;
	int		changed;
	t_cmd	*current;

	i = 0;
	changed = 0;
	current = data->cmd_lst;
	eq_i = equal_index(current->args[index]);
	while (data->envp[i])
	{
		if (!ft_strncmp(current->args[index], data->envp[i], eq_i)
			&& data->envp[i][eq_i] == '=')
		{
			free(data->envp[i]);
			data->envp[i] = ft_strdup(current->args[index]);
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
