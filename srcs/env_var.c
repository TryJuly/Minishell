/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:58:16 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/31 12:04:20 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	count_dollars(char *str)
{
	int	i;
	int	par;
	int	count;

	i = 0;
	count = 0;
	par = 0;
	while (str[i])
	{
		if (str[i] == '$' && par == 0)
			count++;
		else if (str[i] == '(')
			par = 1;
		else if (str[i] == ')')
			par = 0;
		i++;
	}
	return (count);
}

void	expand_quote(char *input, int *i, int *j)
{
	if (input[*i] == '\'')
	{
		*j = *i + ending_quote(&input[*i], '\'');
	}
	else if (input[*i] == '\"')
	{
		*j = *i +ending_quote(&input[*i], '\"');
	}
}

char	*help_split_dollars(char *input, int *i, int *j)
{
	char	*temp;

	*j = *i + 1;
	if (input[*j] == '(')
	{
		while (input[*j] != ')')
			*j += 1;
		*j += 1;
	}
	else if (input[*i] == '\'' || input[*i] == '\"')
		expand_quote(input, i, j);
	else
	{
		while (input[*j] != ' ' && input[*j] && input[*j] != '$')
			*j += 1;
	}
	temp = ft_substr(input, *i, *j - *i + 1);
	*i = *j;
	return (temp);
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
		if (input[i] == '$' || input[i] == '\'' || input[i] == '\"')
			temp = help_split_dollars(input, &i, &j);
		else
		{
			j = i + 1;
			while ((input[j] != '$' && input[j] != '\'' && input[j] != '\"') && input[j])
				j++;
			temp = ft_substr(input, i, j - i);
			i = j - 1;
		}
		res[res_i++] = ft_strdup(temp);
		free(temp);
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
	res = NULL;
	while (tab[i])
	{
		if (!res)
			temp = ft_strdup("");
		if (res)
		{
			temp = ft_strdup(res);
			free(res);
		}
		res = ft_strjoin(temp, tab[i]);
		if (temp[0] != 0)
			free(temp);
		i++;
	}
	return (res);
}

char	*ft_random(char *str)
{
	char	*res;

	if (str[0] == '\'')
		return (str);
	else if (str[0] == '\"')
	{
		res = ft_strtrim(str, "\"");
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
		if (exp_vars[i][0] == '\'' || exp_vars[i][0] == '\"')
			exp_vars[i] = ft_random(exp_vars[i]);
		if (exp_vars[i][0] == '$')
			exp_vars[i] = expand_var_value(exp_vars[i], data);
		i++;
	}
	data->input = ft_unsplit(exp_vars);
}
