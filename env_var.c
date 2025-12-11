/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:58:16 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/11 13:49:29 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*expand_var_value(char *new_str, t_data *data)
{
	int		i;
	char	*temp;
	char	*value;

	i = 0;
	temp = new_str;
	temp += 1;
	if (new_str[1] == '?')
	{
		value = ft_itoa(g_exit_status);
		return (value);
	}
	while (data->envp[i])
	{
		if (ft_strncmp(temp, data->envp[i], ft_strlen(temp) - 1) == 0)
		{
			value = ft_strchr(data->envp[i], '=');
			value += 1;
			return (value);
		}
		i++;
	}
	value = "";
	return (value);
}

int	count_dollars(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

void	merge_dollars(char *str, t_data *data, int index)
{
	char	*res;
	char	*temp;
	char	*exp;
	int		i;
	int		j;

	i = 0;
	res = "";
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = i + 1;
			if (str[j] == '?')
			{
				temp = ft_itoa(g_exit_status);
				res = ft_strjoin(res, temp);
				i++;
				continue ;
			}
			while (str[j] != '$' && str[j] != ' ' && str[j] != 0)
				j++;
			temp = ft_substr(str, i + 1, j - i - 1);
			exp = expand_var_value(temp, data);
			res = ft_strjoin(res, exp);
			i = j;
		}
		else
		{
			j = i + 1;
			while (str[j] != '$' && str[j])
				j++;
			temp = ft_substr(str, i + 1, j - i - 1);
			res = ft_strjoin(res, temp);
			i = j;
		}
		i++;
	}
	data->cmd_lst->args[index] = res;
}

void	expand_var(t_data *data)
{
	char	*new_str;
	int		i;

	i = 1;
	while (data->cmd_lst->args[i])
	{
		if (data->cmd_lst->args[i][0] == '$' &&
				ft_strlen(data->cmd_lst->args[i]) == 1)
		{
			i++;
			continue ;
		}
		else if (data->cmd_lst->args[i][0] == '$')
		{
			if (count_dollars(data->cmd_lst->args[i]) > 1)
				merge_dollars(data->cmd_lst->args[i], data, i);
			else
			{
				new_str = data->cmd_lst->args[i];
				new_str += 1;
				new_str = expand_var_value(new_str, data);
				free(data->cmd_lst->args[i]);
				data->cmd_lst->args[i] = ft_strdup(new_str);
			}
		}
		i++;
	}
}

char	**ft_split_dollars(char *input, int dollars)
{
	int		i;
	int		j;
	int		res_i;
	char	**res;
	char	*temp;

	i = 0;
	res_i = 0;
	res = malloc(sizeof(char *) * (dollars + 1));
	while (input[i])
	{
		if (input[i] == '$')
		{
			j = i + 1;
			while (input[j] != ' ' && input[j] && input[j] != '$')
				j++;
			temp = ft_substr(input, i, j - i);
			i = j - 1;
		}
		else
		{
			j = i + 1;
			while (input[j] != '$' && input[j])
				j++;
			temp = ft_substr(input, i, j - i);
			i = j - 1;
		}
		res[res_i++] = ft_strdup(temp);
		i++;
	}
	res[res_i] = NULL;
	return (res);
}

char	*ft_unsplit(char **tab)
{
	char	*res;
	char	*temp;
	int		i;

	i = 0;
	res = ft_strdup("");
	while (tab[i])
	{
		temp = ft_strdup(res);
		free(res);
		res = ft_strjoin(temp, tab[i]);
		free(temp);
		i++;
	}
	return (res);
}

void	new_expand_var(t_data *data)
{
	char	**exp_vars;
	int		dollars;
	int		i;

	i = 0;
	dollars = count_dollars(data->input);
	if (dollars == 0)
		return ;
	exp_vars = ft_split_dollars(data->input, dollars);
	while (exp_vars[i])
	{
		if (exp_vars[i][0] == '$')
			exp_vars[i] = expand_var_value(exp_vars[i], data);
		i++;
	}
	data->input = ft_unsplit(exp_vars);
}
