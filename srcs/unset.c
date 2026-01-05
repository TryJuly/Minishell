/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:21:05 by cbezenco          #+#    #+#             */
/*   Updated: 2026/01/05 09:50:23 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_unset_arg(t_data *data)
{
	int		i;
	int		offset;
	int		envp_size;
	char	**new_envp;

	i = 0;
	offset = 0;
	envp_size = arr_size(data->envp);
	new_envp = malloc((sizeof(char *) * (envp_size)));
	if (!new_envp)
		printf("pas bon\n");
	while (data->envp[i + offset])
	{
		if (ft_strncmp(data->envp[i + offset],
				data->cmd_lst->args[1], ft_strlen(data->cmd_lst->args[1])) == 0)
		{
			offset += 1;
			continue ;
		}
		new_envp[i] = ft_strdup(data->envp[i + offset]);
		i++;
	}
	new_envp[i] = NULL;
	free_classic(data->envp);
	data->envp = new_envp;
}

int	arg_exist(char *arg, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], arg, ft_strlen(arg)) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_unset(t_data *data)
{
	int	i;

	i = 1;
	if (data->cmd_lst->args[i] == NULL)
		return ;
	while (data->cmd_lst->args[i])
	{
		if (arg_exist(data->cmd_lst->args[1], data->envp))
			ft_unset_arg(data);
		i++;
	}
}
