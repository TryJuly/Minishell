/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:21:05 by cbezenco          #+#    #+#             */
/*   Updated: 2026/02/03 14:29:05 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	ft_len_env(char *str, char *unset);
static int	is_valid_identifier(char *argument);
static int	remove_from_env(t_data *data, char *unset, int j);

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
			remove_from_env(data, data->cmd_lst->args[i], 0);
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
	return (exit_status(status, 1), status);
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

static int	remove_from_env(t_data *data, char *unset, int j)
{
	int		i;
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
		if (!ft_len_env(data->envp[i + j], unset))
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

static int	ft_len_env(char *str, char *unset)
{
	int	i;
	int	len_unset;

	i = 0;
	len_unset = ft_strlen(unset);
	while (str[i] && str[i] != '=')
		i++;
	if (i == len_unset && ft_strncmp(str, unset, i) == 0)
		return (0);
	return (1);
}
