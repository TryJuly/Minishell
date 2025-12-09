/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:58:16 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/09 14:12:52 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*expand_var_value(char *new_str, t_data *data)
{
	int		i;
	char	*value;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(new_str, data->envp[i], ft_strlen(new_str) - 1) == 0)
		{
			value = ft_strchr(data->envp[i], '=');
			value += 1;
			return (value);
		}
		i++;
	}
	value = "";
	return (value);
}

int	count_dollars(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

void	expand_var(t_data *data)
{
	char	*new_str;
	int		i;

	i = 0;
	while (data->arg[i])
	{
		if (data->arg[i][0] == '$' && ft_strlen(data->arg[i]) == 1)
		{
			i++;
			continue ;
		}
		else if (data->arg[i][0] == '$')
		{
			if (count_dollars(data->arg[i]) > 1)
			{
				merge_dollars();
			}
			new_str = data->arg[i];
			new_str += 1;
			new_str = expand_var_value(new_str, data);
			free(data->arg[i]);
			data->arg[i] = ft_strdup(new_str);
		}
		i++;
	}
}
