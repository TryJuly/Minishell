/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:06:07 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/09 12:15:18 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
// mettre dans un fichier utils ?
int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	set_new_env_var(t_data *data)
{
	int		envp_size;
	char	**new_envp;
	int		i;

	i = 0;
	envp_size = arr_size(data->envp);
	new_envp = malloc(sizeof(char *) * (envp_size + 1));
	if (!new_envp)
		printf("pas bon");
	while (data->envp[i])
	{
		new_envp[i] = ft_strdup(data->envp[i]);
		i++;
	}
	new_envp[i] = data->arg[0];
	new_envp[i + 1] = NULL;
	ft_free_array(data->envp);
	data->envp = new_envp;
}

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
	eq_i = equal_index(data->arg[0]);
	while (data->envp[i])
	{
		if (ft_strncmp(data->arg[0], data->envp[i], eq_i) == 0)
		{
			data->envp[i] = ft_strdup(data->arg[0]);
			changed = 1;
		}
		i++;
	}
	return (changed);
}

void	var_setup(t_data *data)
{
	int		i;

	i = 0;
	while (data->arg[0][i])
	{
		if (data->arg[0][i] == '=' && data->arg[0][i + 1])
			return ;
		i++;
	}
	if (data->arg[0][i - 1] == '=')
		return ;
	else if (data->arg[0][i] == '\0')
		data->arg[0] = ft_strjoin(data->arg[0], "=");
}

void	ft_export(t_data *data)
{
	if (!data->arg[0])
	{
		ft_env(data);
		return ;
	}
	while (data->arg[0])
	{
		var_setup(data);
		if (!change_env_var(data))
			set_new_env_var(data);
		data->arg += 1;
	}
}
