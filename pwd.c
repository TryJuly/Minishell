/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:22:29 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/11 13:58:09 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*get_pwd(char **envp)
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

void	ft_pwd(t_data *data)
{
	char	*buf;

	if (data->cmd_lst->args[1] == NULL)
	{
		buf = get_pwd(data->envp);
		if (!buf)
		{
			g_exit_status = 1;
			printf("pwd : no PWD env found\n");
			return ;
		}
		printf("%s\n", buf);
	}
	else
	{
		g_exit_status = 1;
		printf("pwd : too many arguments\n");
	}
}
