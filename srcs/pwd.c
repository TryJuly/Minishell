/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:22:29 by cbezenco          #+#    #+#             */
/*   Updated: 2026/01/23 16:44:19 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*get_pwd(char **envp);

void	ft_pwd(t_data *data)
{
	char	*buf;

	if (data->cmd_lst->args[1] == NULL)
	{
		buf = get_pwd(data->envp);
		if (!buf)
		{
			g_exit_status = 1;
			ft_putstr_fd("Msh: pwd : no PWD env found\n", 2);
			return ;
		}
		printf("%s\n", buf);
		g_exit_status = 0;
	}
	else
	{
		printf("%s\n", get_pwd(data->envp));
		g_exit_status = 0;
	}
}

static char	*get_pwd(char **envp)
{
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			temp = envp[i];
			break ;
		}
		i++;
	}
	if (!temp)
		return (temp);
	temp = ft_strchr(temp, '/');
	return (temp);
}
