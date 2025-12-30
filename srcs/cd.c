/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:51:33 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/30 12:06:52 by cbezenco         ###   ########.fr       */
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
		data->envp[old_i] = ft_strjoin("OLDPWD=", old);
	if (!(new_i == -1))
		data->envp[new_i] = ft_strjoin("PWD=", new);
	free(old);
	free(new);
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
		printf("No HOME env var.\n");
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
		printf("No such file or directory: ");
		printf("%s\n", temp);
		return ;
	}
	if (chdir(temp) == -1)
		printf("oups");
	new_pwd = malloc(100);
	if (!new_pwd)
		return ;
	new_pwd = getcwd(new_pwd, 100);
	update_env_pwd(data, old, new_pwd);
}

void	ft_cd_2(t_data *data, char *old_pwd)
{
	char	*new_pwd;

	if (access(data->cmd_lst->args[1], F_OK) == -1)
	{
		printf("No such file or directory: ");
		perror(data->cmd_lst->args[1]);
		return ;
	}
	if (chdir(data->cmd_lst->args[1]) == -1)
		printf("oups");
	new_pwd = malloc(100);
	if (!new_pwd)
	{
		printf("OH YEE-NOOOOOOOOOO\n");
		return ;
	}
	new_pwd = getcwd(new_pwd, 100);
	update_env_pwd(data, old_pwd, new_pwd);
}

void	ft_cd(t_data *data)
{
	char	*old_pwd;

	if (data->cmd_lst->args[2])
	{
		g_exit_status = 1;
		ft_putstr_fd("too many arguments\n", 2);
		return ;
	}
	old_pwd = malloc(100);
	if (!old_pwd)
	{
		printf("OH NOOOOOOOOOOOO\n");
		return ;
	}
	old_pwd = getcwd(old_pwd, 100);
	if (data->cmd_lst->args[1] == NULL)
		cd_home(data, old_pwd);
	else
		ft_cd_2(data, old_pwd);
}
