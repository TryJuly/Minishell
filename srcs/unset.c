/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:21:05 by cbezenco          #+#    #+#             */
/*   Updated: 2026/01/23 17:17:12 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	is_valid_identifier(char *argument);
static int	remove_from_env(t_data *data, char *unset);

int	ft_unset(t_data *data)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!data->cmd_lst->args[i])
		return (0);
	while (data->cmd_lst->args[i])
	{
		if (!is_valid_identifier(data->cmd_lst->args[i]))
		{
			remove_from_env(data, data->cmd_lst->args[i]);
		}
		else
		{
			ft_putstr_fd("Msh: unset: `", 2);
			ft_putstr_fd(data->cmd_lst->args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			status = 1;
		}
		i++;
	}
	return (g_exit_status = status, status);
}

static int	is_valid_identifier(char *argument)
{
	int	i;

	if (!argument || !argument[0])
		return (1);
	i = 1;
	if (!ft_isalpha(argument[0]) && argument[0] != '_')
		return (1);
	while (argument[i])
	{
		if (!ft_isalnum(argument[i]) && argument[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static int	remove_from_env(t_data *data, char *unset)
{
	int		i;
	int		j;
	int		envp_size;
	char	**new_envp;

	i = 0;
	j = 0;
	envp_size = arr_size(data->envp);
	new_envp = malloc(sizeof(char *) * envp_size);
	if (!new_envp)
		return (error_malloc(), 1);
	while (data->envp[i + j])
	{
		if (ft_strncmp(unset, data->envp[i + j], ft_strlen(unset)) == 0)
		{
			j++;
			continue ;
		}
		new_envp[i] = ft_strdup(data->envp[i + j]);
		i++;
	}
	new_envp[i] = NULL;
	free_classic(data->envp);
	data->envp = new_envp;
	return (0);
}
