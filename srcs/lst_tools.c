/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 08:29:45 by strieste          #+#    #+#             */
/*   Updated: 2025/12/22 13:33:39 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
/*			SUPP FUNCTION			*/
void	print_lst(t_cmd *lst)
{
	size_t	count;
	size_t	len;
	t_redir	*tmp;

	len = 0;
	while (lst)
	{
		count = 0;
		while (lst->args[count])
		{
			printf("Argument %ld: %s\n", count, lst->args[count]);
			count++;
		}
		printf("%sPrint file redir%s\n", YELLOW, NC);
		tmp = lst->redir;
		while (tmp)
		{
			printf("%sFile : :%s:%s\n", GREEN, tmp->file, NC);
			printf("%sFile type : %d%s\n", GREEN, tmp->type, NC);
			tmp = tmp->next;
		}
		lst = lst->next;
		len++;
	}
	printf("Numbers of node : %ld\n", len);
}

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

t_cmd	*lst_last(t_cmd *cmd)
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
