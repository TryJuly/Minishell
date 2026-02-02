/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:51:33 by cbezenco          #+#    #+#             */
/*   Updated: 2026/01/23 16:24:00 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	update_env_pwd(t_data *data, char *old, char *new)
{
	int	i;
	int	old_i;
	int	new_i;

	i = 0;
	old_i = -1;
	new_i = -1;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PWD", 3) == 0)
			new_i = i;
		else if (ft_strncmp(data->envp[i], "OLDPWD", 6) == 0)
			old_i = i;
		i++;
	}
	if (!(old_i == -1))
	{
		free(data->envp[old_i]);
		data->envp[old_i] = ft_strjoin("OLDPWD=", old);
	}
	if (!(new_i == -1))
	{
		free(data->envp[new_i]);
		data->envp[new_i] = ft_strjoin("PWD=", new);
	}
}

int	cd_home(t_data *data, char *old)
{
	char	*home_path;
	char	*new_pwd;

	home_path = get_env_value("HOME", data);
	if (!home_path || home_path[0] == '\0')
	{
		ft_putstr_fd("Msh: cd: HOME not set\n", 2);
		return (free(home_path), g_exit_status = 1, 1);
	}
	if (chdir(home_path) == -1)
	{
		ft_putstr_fd("Msh: cd : ", 2);
		perror(home_path);
		return (free(home_path), g_exit_status = 1, 1);
	}
	free(home_path);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		ft_putstr_fd("Msh: cd: getcwd\n", 2);
		return (g_exit_status = 1, 1);
	}
	update_env_pwd(data, old, new_pwd);
	free(new_pwd);
	return (g_exit_status = 0, 0);
}

void	ft_cd_2(t_data *data, char *old_pwd)
{
	char	*new_pwd;

	if (chdir(data->cmd_lst->args[1]) == -1)
	{
		ft_putstr_fd("Msh: cd: ", 2);
		perror(data->cmd_lst->args[1]);
		g_exit_status = 1;
		return ;
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		ft_putstr_fd("Msh: cd: getcwd\n", 2);
		g_exit_status = 1;
		return ;
	}
	update_env_pwd(data, old_pwd, new_pwd);
	free(new_pwd);
	g_exit_status = 0;
}

void	ft_cd(t_data *data)
{
	char	*old_pwd;
	char	*target;

	if (arr_size(data->cmd_lst->args) >= 3)
	{
		ft_putstr_fd("Msh: cd: too many arguments\n", 2);
		g_exit_status = 1;
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		ft_putstr_fd("Msh: cd: getcwd\n", 2);
		g_exit_status = 2;
		return ;
	}
	target = data->cmd_lst->args[1];
	if (target == NULL || !ft_strncmp(target, "~", 2))
		cd_home(data, old_pwd);
	else
		ft_cd_2(data, old_pwd);
	free(old_pwd);
}
