/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:26:58 by strieste          #+#    #+#             */
/*   Updated: 2025/12/26 12:27:19 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_builtin(t_data *data, t_cmd *cmd)
{
	data->cmd_lst = cmd;
	if (ft_strncmp("echo", data->cmd_lst->args[0], 5) == 0)
		ft_echo(data);
	else if (ft_strncmp("env", data->cmd_lst->args[0], 4) == 0)
		ft_env(data);
	else if (ft_strncmp("pwd", data->cmd_lst->args[0], 4) == 0)
		ft_pwd(data);
	else if (ft_strncmp("cd", data->cmd_lst->args[0], 3) == 0)
		ft_cd(data);
	else if (ft_strncmp("export", data->cmd_lst->args[0], 7) == 0)
		ft_export(data);
	else if (ft_strncmp("unset", data->cmd_lst->args[0], 6) == 0)
		ft_unset(data);
	else if (ft_strncmp("exit", data->cmd_lst->args[0], 5) == 0)
		ft_exit(data);
	else
		return (0);
	return (1);
}
