/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 08:29:45 by strieste          #+#    #+#             */
/*   Updated: 2026/01/23 16:42:36 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_cmd	*lst_last(t_cmd *cmd);

void	add_back_lst(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*tmp;

	if (!new)
		return ;
	if (!(*cmd))
	{
		(*cmd) = new;
		return ;
	}
	if (!(*cmd)->next)
	{
		(*cmd)->next = new;
		return ;
	}
	tmp = lst_last(*cmd);
	tmp->next = new;
	return ;
}

static t_cmd	*lst_last(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	lst_size(t_cmd *cmd)
{
	size_t	len;
	t_cmd	*tmp;

	if (!cmd)
		return (0);
	len = 0;
	tmp = cmd;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}
