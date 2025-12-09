/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:51:33 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/09 15:15:14 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	update_env_pwd(t_data *data, char *old, char *new)
{
	int	i;
	int	old_i;
	int	new_i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PWD", 3) == 0)
			new_i = i;
		else if (ft_strncmp(data->envp[i], "OLDPWD", 6) == 0)
			old_i = i;
		i++;
	}
	data->envp[old_i] = ft_strjoin("OLDPWD=", old);
	data->envp[new_i] = ft_strjoin("PWD=", new);
	free(old);
	free(new);
}

void	cd_home(t_data *data, char *old)
{
	int		i;
	char	*new_pwd;
	char	*temp;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "HOME", 4) == 0)
			break ;
		i++;
	}
	temp = ft_strchr(data->envp[i], '/');
	if (access(temp, F_OK) == -1)
	{
		printf("No such file or directory: ");
		perror(data->cmd_lst->args[1]);
		return ;
	}
	if (chdir(temp) == -1)
		printf("oups");
	new_pwd = malloc(100);
	new_pwd = getcwd(new_pwd, 100);
	update_env_pwd(data, old, new_pwd);
	free(new_pwd);
}

void	ft_cd(t_data *data)
{
	char	*new_pwd;
	char	*old_pwd;

	old_pwd = malloc(100); // valeur a determiner
	old_pwd = getcwd(old_pwd, 100);
	if (data->cmd_lst->args[1] == NULL)
		cd_home(data, old_pwd);
	else
	{
		if (access(data->cmd_lst->args[1], F_OK) == -1)
		{
			printf("No such file or directory: ");
			perror(data->cmd_lst->args[1]);
			return ;
		}
		if (chdir(data->cmd_lst->args[1]) == -1)
			printf("oups");
		new_pwd = malloc(100);
		new_pwd = getcwd(new_pwd, 100);
		update_env_pwd(data, old_pwd, new_pwd);
	}
}
