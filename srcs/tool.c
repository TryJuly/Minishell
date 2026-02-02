/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 08:42:45 by strieste          #+#    #+#             */
/*   Updated: 2026/01/29 12:18:26 by strieste         ###   ########.fr       */
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

char	*remove_quote(char *str)
{
	int		i;
	int		j;
	char	*res;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	res = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!res)
		return (error_malloc(), NULL);
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && quote == 0)
			quote = str[i++];
		else if (str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

char	*get_env_value(char *var_name, t_data *data)
{
	int	i;
	int	name_len;

	if (!var_name ||!*var_name)
		return (NULL);
	i = 0;
	name_len = ft_strlen(var_name);
	if (ft_strncmp(var_name, "?", 2) == 0)
		return (ft_itoa(g_exit_status));
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], var_name, name_len)
			&& data->envp[i][name_len] == '=')
		{
			return (ft_strdup(data->envp[i] + name_len + 1));
		}
		i++;
	}
	return (ft_strdup(""));
}
