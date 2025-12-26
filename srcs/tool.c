/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 08:42:45 by strieste          #+#    #+#             */
/*   Updated: 2025/12/26 12:21:16 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	operator(char c, char next, char **str)
{
	if (c == '>' && next == '>')
	{
		*str = ft_strdup(">>");
		if (!*str)
			return (-1);
		return (2);
	}
	if (c == '<' && next == '<')
	{
		*str = ft_strdup("<<");
		if (!*str)
			return (-1);
		return (2);
	}
	if (c == '<' || c == '>' || c == '|')
	{
		*str = dup_char(c);
		if (!*str)
			return (-1);
		return (1);
	}
	return (0);
}

int	skip_space(char *str)
{
	size_t	count;

	count = 0;
	while (str[count] && str[count] == ' ')
		count++;
	return (count);
}

int	count_args(char **array, int len)
{
	size_t	count;

	count = 0;
	while (array[len] && array[len][0] != '|')
	{
		if (is_redir(array[len]))
		{
			if (array[len + 1])
				len += 2;
			else
				return (-1);
		}
		else
		{
			len++;
			count++;
		}
	}
	return (count);
}

t_cmd	*malloc_args(char **array, size_t len)
{
	t_cmd	*current;

	current = ft_calloc(1, sizeof(t_cmd));
	if (!current)
		return (ft_putstr_fd("Msh: Error malloc fill_lst\n", 2), NULL);
	current->args = ft_calloc(count_args(array, len) + 1, sizeof(char *));
	if (!current->args)
		return (ft_putstr_fd("Msh: Error malloc fill_lst", 2), NULL);
	current->redir = NULL;
	current->next = NULL;
	return (current);
}

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
