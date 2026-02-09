/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_expand_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:26:51 by strieste          #+#    #+#             */
/*   Updated: 2026/02/03 11:19:55 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	help_loop(t_cmd *cmd, t_data *data);

int	replace_var_value(t_data *data)
{
	t_cmd	*current;

	current = data->cmd_lst;
	while (current)
	{
		if (help_loop(current, data) == 1)
			return (1);
		current = current->next;
	}
	return (0);
}

static int	help_loop(t_cmd *cmd, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd->args[i] && cmd->args)
	{
		tmp = NULL;
		if (i > 0 && ft_strncmp(cmd->args[i - 1], "<<", 3) == 0)
		{
			i++;
			continue ;
		}
		cmd->args[i] = expand_token(cmd->args[i], data);
		tmp = remove_quote(cmd->args[i]);
		if (!tmp)
			return (error_malloc(), 1);
		free(cmd->args[i]);
		cmd->args[i] = tmp;
		i++;
	}
	return (0);
}
