/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:58:23 by strieste          #+#    #+#             */
/*   Updated: 2025/12/09 14:29:54 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_cmd	*fill_lst(char **array)
{
	size_t	len;
	size_t	count;
	char	**cmd_array;
	t_cmd	*cmd;
	t_cmd	*data;

	len = 0;
	while (array[len])
	{
		count = 0;
		while (array[len + count][0] != '|' && array[len + count])
			count++;
		cmd_array = malloc((count + 1) * sizeof(char**));
		if (!cmd_array)
			return (printf("%sError fill_lst%s\n", RED, NC), NULL);
		while (len <= count)
			cmd_array[len] = array[len++];
		cmd_array[len] = 0;
		cmd = new_node(cmd_array);
		add_back(data, cmd);
		ft_free_array(&cmd_array);
	}
	return (data);
}

t_cmd	*new_node(char **cmd)
{
	t_cmd	*new;
	size_t	len;

	len = 0;
	while (cmd[len])
	{
		if (cmd[len] == '<')
		{
			new->in = ft_strdup(cmd[len + 1]);
			len += 2;
		}
		if (cmd[len] == '|' && !cmd[len + 1])
		{
			new->out = ft_strdup(cmd[len]);
			len++;
		}
		if (cmd[len] == '|' && cmd[len + 1])
		{
			new->in = ft_strdup(cmd[len]);
			len++;
		}	
	}
}

void	add_back(t_cmd *cmd, t_cmd *new)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return ;
}
