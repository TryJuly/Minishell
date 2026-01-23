/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 08:42:45 by strieste          #+#    #+#             */
/*   Updated: 2026/01/23 13:05:15 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	count_args(char **array, int len);

t_cmd	*malloc_args(char **array, size_t len)
{
	t_cmd	*current;

	current = ft_calloc(1, sizeof(t_cmd));
	if (!current)
		return (error_malloc(), NULL);
	current->args = ft_calloc(count_args(array, len) + 1, sizeof(char *));
	if (!current->args)
		return (error_malloc(), free(current), NULL);
	current->redir = NULL;
	current->next = NULL;
	return (current);
}

static int	count_args(char **array, int len)
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

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

// int	skip_space(char *str)
// {
// 	size_t	count;

// 	count = 0;
// 	while (str[count] && str[count] == ' ')
// 		count++;
// 	return (count);
// }
