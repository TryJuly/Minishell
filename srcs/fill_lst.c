/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:58:23 by strieste          #+#    #+#             */
/*   Updated: 2025/12/22 13:51:50 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		add_redir_node(char *redir, char *file, t_cmd *current);
static void		add_args_node(char *argument, t_cmd *current);
static int		get_redir_type(char *redir);

t_cmd	*fill_lst(char **array)
{
	size_t	len;
	t_cmd	*lst;
	t_cmd	*current;

	len = 0;
	lst = NULL;
	current = NULL;
	while (array[len])
	{
		current = malloc_args(array, len);
		while (array[len] && array[len][0] != '|')
		{
			if (is_redir(array[len]))
			{
				add_redir_node(array[len], array[len + 1], current);
				len += 2;
			}
			else
				add_args_node(array[len++], current);
		}
		add_back_lst(&lst, current);
		if ((array[len]) && array[len][0] == '|' && array[len + 1])
			len++;
	}
	return (lst);
}

static void	add_redir_node(char *redir, char *file, t_cmd *current)
{
	t_redir	*new;
	t_redir	*tmp;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
	{
		printf("%sMsh: Error Malloc add_redir_node%s\n", RED, NC);
		return ;
	}
	new->type = get_redir_type(redir);
	new->file = ft_strdup(file);
	new->next = NULL;
	if (current->redir == NULL)
		current->redir = new;
	else
	{
		tmp = current->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	add_args_node(char *argument, t_cmd *current)
{
	size_t	count;

	count = 0;
	if (!current->args[0])
	{
		if (argument[0] == '"' || argument[0] == '\'')
			current->args[0] = ft_strtrim(argument, "\"'");
		else
			current->args[0] = ft_strdup(argument);
		current->args[1] = NULL;
	}
	else
	{
		while (current->args[count])
			count++;
		if (argument[0] == '"' || argument[0] == '\'')
			current->args[count++] = ft_strtrim(argument, "\"'");
		else
			current->args[count++] = ft_strdup(argument);
		current->args[count] = 0;
	}
	return ;
}

int	is_redir(char *str)
{
	if (ft_strlen(str) == 1)
	{
		if (str[0] == '>' || str[0] == '<')
			return (1);
	}
	else if (ft_strlen(str) == 2)
	{
		if (str[0] == '>' && str[1] == '>')
			return (1);
		if (str[0] == '<' && str[1] == '<')
			return (1);
	}
	return (0);
}

static int	get_redir_type(char *redir)
{
	if (ft_strlen(redir) == 2 && redir[0] == '>' && redir[1] == '>')
		return (R_APPEND);
	if (ft_strlen(redir) == 2 && redir[0] == '<' && redir[1] == '<')
		return (R_HEREDOC);
	if (ft_strlen(redir) == 1 && redir[0] == '>')
		return (R_OUT);
	if (ft_strlen(redir) == 1 && redir[0] == '<')
		return (R_IN);
	return (-1);
}
