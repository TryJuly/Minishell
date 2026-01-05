/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:58:16 by cbezenco          #+#    #+#             */
/*   Updated: 2026/01/05 11:19:33 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	help_new_expand(char **tab, t_data *data);
static void	help_count_dollar_v1(char *str, int *quote, int *count);
static void	help_count_dollar_v2(char *str, int *quote, int *count, int *par);

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
		help_count_dollar_v1(&str[i], &quote, &count);
		if (str[i] == ' ' && !quote)
		{
			while (str[i] == ' ')
				i++;
			count++;
			continue ;
		}
		help_count_dollar_v2(&str[i], &quote, &count, &par);
		i++;
	}
	return (count);
}

static void	help_count_dollar_v1(char *str, int *quote, int *count)
{
	int	i;

	i = 0;
	if (str[i] == '\'' && !*quote)
		*quote += 1;
	else if (str[i] == '\'' && *quote)
	{
		*quote -= 1;
		*count += 1;
	}
	if (str[i] == '"' && !*quote)
		*quote += 1;
	else if (str[i] == '"' && *quote)
	{
		*quote -= 1;
		*count += 1;
	}
	return ;
}

static void	help_count_dollar_v2(char *str, int *quote, int *count, int *par)
{
	int i;

	i = 0;
	if (str[i] == '(')
		*par = 1;
	if (str[i] == ')')
		*par = 0;
	if (str[i] == '$' && !*quote && *par == 0)
		*count += 1;
	return ;
}


// void	help_count_dollar(char *str, int *quote, int *count)
// {
// 	int i;

// 	i = 0;
// 	if (str[i] == '\'' && !*quote)
// 		*quote++;
// 	else if (str[i] == '\'' && *quote)
// 	{
// 		*quote--;
// 		*count++;
// 	}
// 	else if (str[i] == '"' && !*quote)
// 		quote++;
// 	else if (str[i] == '"' && quote)
// 	{
// 		quote--;
// 		*count++;
// 	}
// }

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
		res[res_i++] = temp;
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
	temp = NULL;
	while (tab[i])
	{
		temp = ft_strjoin(res, tab[i]);
		if (!temp && !res)
			return (NULL);
		else if (!temp && res)
		{
			free(res);
			return (NULL);
		}
		if (res)
			free(res);
		res = temp;
		i++;
	}
	return (res);
}

// char	*ft_unsplit(char **tab)
// {
// 	char	*res;
// 	char	*temp;
// 	int		i;

// 	i = 0;
// 	res = NULL;
// 	while (tab[i])
// 	{
// 		if (!res)
// 			temp = ft_strdup("");
// 		if (res)
// 		{
// 			temp = ft_strdup(res);
// 			free(res);
// 		}
// 		res = ft_strjoin(temp, tab[i]);
// 		if (temp[0] != 0)
// 			free(temp);
// 		i++;
// 	}
// 	return (res);
// }

char	*redo_expand_var(char *str, t_data *data)
{
	char	**exp_vars;
	int		dollars;
	int		i;
	char	*tmp;

	i = 0;
	dollars = count_dollars(str);
	if (dollars == 0)
		return (str);
	exp_vars = ft_split_dollars(str, dollars);
	while (exp_vars[i])
	{
		if (exp_vars[i][0] == '"')
		{
			tmp = ft_strtrim(exp_vars[i], "\"");
			free(exp_vars[i]);
			exp_vars[i] = redo_expand_var(tmp, data);
			free(tmp);
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
	char	*tmp;

	i = 0;
	dollars = count_dollars(data->input);
	if (!no_dollars(data->input))
		return ;
	exp_vars = ft_split_dollars(data->input, dollars);
	while (exp_vars[i])
	{
		help_new_expand(&exp_vars[i], data);
		i++;
	}
	tmp = ft_unsplit(exp_vars);
	ft_free_array(&exp_vars);
	free(data->input);
	data->input = tmp;
}

static int	help_new_expand(char **tab, t_data *data)
{
	char *tmp;
	
	if (*tab[0] == '"')
		{
			tmp = ft_strtrim(*tab, "\"");
			if (!tmp)
				return (1);
			*tab = redo_expand_var(tmp, data);
			if (!*tab)
				return (1);
			free(tmp);
		}
		if (*tab[0] == '$')
		{
			tmp = expand_var_value(*tab, data);
			if (!tmp)
				return (1);
			free(*tab);
			*tab = tmp;
		}
		return (0);
}
