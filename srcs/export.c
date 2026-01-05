/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:06:07 by cbezenco          #+#    #+#             */
/*   Updated: 2026/01/05 09:49:37 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	set_new_env_var(t_data *data)
{
	int		envp_size;
	char	**new_envp;
	int		i;

	i = 0;
	envp_size = arr_size(data->envp);
	new_envp = malloc(sizeof(char *) * (envp_size + 2));
	if (!new_envp)
		printf("pas bon");
	while (data->envp[i])
	{
		new_envp[i] = ft_strdup(data->envp[i]);
		i++;
	}
	new_envp[i] = ft_strdup(data->cmd_lst->args[1]);
	new_envp[i + 1] = NULL;
	free_classic(data->envp);
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
	eq_i = equal_index(data->cmd_lst->args[1]);
	while (data->envp[i])
	{
		if (ft_strncmp(data->cmd_lst->args[1], data->envp[i], eq_i) == 0)
		{
			data->envp[i] = ft_strdup(data->cmd_lst->args[1]);
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
	while (data->cmd_lst->args[1][i])
	{
		if (data->cmd_lst->args[1][i] == '=' && data->cmd_lst->args[1][i + 1])
			return ;
		i++;
	}
	if (data->cmd_lst->args[1][i - 1] == '=')
		return ;
	else if (data->cmd_lst->args[1][i] == '\0')
		data->cmd_lst->args[1] = ft_strjoin(data->cmd_lst->args[1], "=");
}

int	valid_identifier(char *str)
{
	int	i;
	int check;

	i = 1;
	if (!ft_isalpha(str[0]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		check = ft_isalnum(str[i]);
		if (check == 0 && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(t_data *data)
{
	int	i;

	i = 1;
	if (!data->cmd_lst->args[i])
	{
		ft_env(data);
		return ;
	}
	while (data->cmd_lst->args[i])
	{
		var_setup(data);
		if (!valid_identifier(data->cmd_lst->args[i]))
		{
			g_exit_status = 1;
			ft_putstr_fd("not valid identifier\n", 2);
			i++;
			continue ;
		}
		if (!change_env_var(data))
			set_new_env_var(data);
		i++;
	}
}
