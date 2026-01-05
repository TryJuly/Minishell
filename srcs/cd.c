/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:51:33 by cbezenco          #+#    #+#             */
/*   Updated: 2026/01/05 13:51:48 by strieste         ###   ########.fr       */
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

void	get_env_home(t_data *data, int *i)
{
	while (data->envp[*i])
	{
		if (ft_strncmp(data->envp[*i], "HOME", 4) == 0)
			break ;
		*i += 1;
	}
	if (!data->envp[*i])
	{
		ft_putstr_fd("Msh: No HOME env var.\n", 2);
		return ;
	}
}

void	cd_home(t_data *data, char *old)
{
	int		i;
	char	*new_pwd;
	char	*temp;

	i = 0;
	get_env_home(data, &i);
	temp = ft_strchr(data->envp[i], '/');
	if (access(temp, F_OK) == -1)
	{
		ft_putstr_fd("Msh: No such file or directory: ", 2);
		ft_putendl_fd(temp, 2);
		g_exit_status = 1;
		return ;
	}
	if (chdir(temp) == -1)
		ft_putstr_fd("Msh: No access to directory\n", 2);
	new_pwd = getcwd(NULL, 0);
	update_env_pwd(data, old, new_pwd);
	free(new_pwd);
}

void	ft_cd_2(t_data *data, char *old_pwd)
{
	char	*new_pwd;

	if (access(data->cmd_lst->args[1], F_OK) == -1)
	{
		ft_putstr_fd("Msh: No such file or directory: ", 2);
		ft_putendl_fd(data->cmd_lst->args[1], 2);
		g_exit_status = 1;
		return ;
	}
	if (chdir(data->cmd_lst->args[1]) == -1)
		printf("Msh: ");
	new_pwd = getcwd(NULL, 0);
	update_env_pwd(data, old_pwd, new_pwd);
	free(new_pwd);
}

void	ft_cd(t_data *data)
{
	char	*old_pwd;

	if (arr_size(data->cmd_lst->args) >= 3)
	{
		g_exit_status = 1;
		ft_putstr_fd("Msh: Too many arguments\n", 2);
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (data->cmd_lst->args[1] == NULL)
		cd_home(data, old_pwd);
	else
		ft_cd_2(data, old_pwd);
	free(old_pwd);
}
