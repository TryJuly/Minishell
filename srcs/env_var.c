/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:58:16 by cbezenco          #+#    #+#             */
/*   Updated: 2026/01/05 09:18:06 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	count_dollars(char *str)
{
	int	i;
	int	par;
	int	count;
	int	quote;

	i = 0;
	count = 0;
	par = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !quote)
			quote++;
		else if (str[i] == '\'' && quote)
		{
			quote--;
			count++;
		}
		else if (str[i] == '"' && !quote)
			quote++;
		else if (str[i] == '"' && quote)
		{
			quote--;
			count++;
		}
		else if (str[i] == ' ' && !quote)
		{
			while (str[i] == ' ')
				i++;
			count++;
			continue ;
		}
		else if (str[i] == '(')
			par = 1;
		else if (str[i] == ')')
			par = 0;
		else if (str[i] == '$' && !quote && par == 0)
			count++;
		i++;
	}
	return (count);
}

void	expand_quote(char *input, int *i, int *j)
{
	if (input[*i] == '\'')
	{
		*j = *i + ending_quote(&input[*i], '\'');
		if (input[*j] == '\'')
			*j += 1;
	}
	else if (input[*i] == '\"')
	{
		*j = *i + ending_quote(&input[*i], '\"');
		if (input[*j] == '"')
			*j += 1;
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
		while ((input[*j] && input[*j] != '$' && input[*j] != ' ') && (input[*j] != '\'' && input[*j] != '"'))
			*j += 1;
	}
	temp = ft_substr(input, *i, *j - *i);
	*i = *j - 1;
	return (temp);
}

char	*blank_space(char *str, int *i, int *j)
{
	char	*temp;

	*j = *i + 1;
	while (str[*j] == ' ')
		*j += 1;
	temp = ft_substr(str, *i, *j - *i);
	*i = *j - 1;
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
		if ((input[i] == '$') || input[i] == '"' || input[i] == '\'')
			temp = help_split_dollars(input, &i, &j);
		else if (input[i] == ' ')
			temp = blank_space(input, &i, &j);
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

char	*redo_expand_var(char *str, t_data *data)
{
	char	**exp_vars;
	int		dollars;
	int		i;

	i = 0;
	dollars = count_dollars(str);
	if (dollars == 0)
		return (str);
	exp_vars = ft_split_dollars(str, dollars);
	while (exp_vars[i])
	{
		if (exp_vars[i][0] == '"')
		{
			exp_vars[i] = ft_strtrim(exp_vars[i], "\"");
			exp_vars[i] = redo_expand_var(exp_vars[i], data);
		}
		if (exp_vars[i][0] == '$')
			exp_vars[i] = expand_var_value(exp_vars[i], data);
		i++;
	}
	str = ft_unsplit(exp_vars);
	return (str);
}

int	no_dollars(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	new_expand_var(t_data *data)
{
	char	**exp_vars;
	int		dollars;
	int		i;

	i = 0;
	dollars = count_dollars(data->input);
	if (!no_dollars(data->input))
		return ;
	exp_vars = ft_split_dollars(data->input, dollars);
	while (exp_vars[i])
	{
		if (exp_vars[i][0] == '"')
		{
			exp_vars[i] = ft_strtrim(exp_vars[i], "\"");
			exp_vars[i] = redo_expand_var(exp_vars[i], data);
		}
		if (exp_vars[i][0] == '$')
			exp_vars[i] = expand_var_value(exp_vars[i], data);
		i++;
	}
	data->input = ft_unsplit(exp_vars);
}
