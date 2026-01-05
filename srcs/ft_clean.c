/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 08:38:46 by strieste          #+#    #+#             */
/*   Updated: 2026/01/05 09:43:06 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_all(t_data *data)
{
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->cmd_lst)
	{
		ft_clear_lst(&data->cmd_lst);
		data->cmd_lst = NULL;
	}
	if (data->envp)
	{
		free_classic(data->envp);
		data->envp = NULL;
	}
	if (data->path)
	{
		free_classic(data->path);
		data->path = NULL;
	}
	if (data->heredoc == 1 && !access("/tmp/heredoc", F_OK))
		unlink("/tmp/heredoc");
	rl_clear_history();
	return ;
}

void	ft_clear_lst(t_cmd **lst)
{
	t_cmd	*s_p;
	t_redir	*p_redir;

	while (*lst)
	{
		s_p = (*lst)->next;
		if ((*lst)->redir)
		{
			p_redir = (*lst)->redir->next;
			while (((*lst)->redir))
			{
				free((*lst)->redir->file);
				free((*lst)->redir);
				(*lst)->redir = p_redir;
			}
		}
		ft_free_array(&(*lst)->args);
		free(*lst);
		(*lst) = s_p;
	}
	(*lst) = NULL;
}

int	ft_free_array(char ***array)
{
	size_t	count;

	if (!array || !(*array))
		return (0);
	count = 0;
	while ((*array)[count])
	{
		free((*array)[count]);
		count++;
	}
	free(*array);
	*array = NULL;
	return (0);
}

void	free_classic(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
