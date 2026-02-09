/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:06:07 by cbezenco          #+#    #+#             */
/*   Updated: 2026/02/03 14:23:32 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	set_new_env_var(t_data *data, int index);
static void	var_setup(t_data *data, int index);
static int	valid_identifier(char *str);

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
		var_setup(data, i);
		if (!valid_identifier(data->cmd_lst->args[i]))
		{
			exit_status(1, 1);
			ft_putstr_fd("Msh: not valid identifier\n", 2);
			i++;
			continue ;
		}
		if (!change_env_var(data, i))
			set_new_env_var(data, i);
		i++;
	}
	exit_status(0, 1);
}

static int	valid_identifier(char *str)
{
	int	i;
	int	check;

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

static void	set_new_env_var(t_data *data, int index)
{
	int		envp_size;
	char	**new_envp;
	int		count;

	count = 0;
	envp_size = arr_size(data->envp);
	new_envp = malloc(sizeof(char *) * (envp_size + 2));
	if (!new_envp)
	{
		error_malloc();
		exit_status(1, 1);
		return ;
	}
	while (data->envp[count])
	{
		new_envp[count] = ft_strdup(data->envp[count]);
		count++;
	}
	new_envp[count] = ft_strdup(data->cmd_lst->args[index]);
	new_envp[count + 1] = NULL;
	free_classic(data->envp);
	data->envp = new_envp;
}

static void	var_setup(t_data *data, int index)
{
	int		count;
	t_cmd	*current;
	char	*tmp;

	count = 0;
	current = data->cmd_lst;
	while (current->args[index][count])
	{
		if (current->args[index][count] == '='
				&& current->args[index][count + 1])
			return ;
		count++;
	}
	if (current->args[index][count - 1] == '=')
		return ;
	else if (current->args[index][count] == '\0')
	{
		tmp = ft_strjoin(current->args[index], "=");
		free(current->args[index]);
		current->args[index] = tmp;
	}
}
