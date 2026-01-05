/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_v3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:24:37 by strieste          #+#    #+#             */
/*   Updated: 2026/01/05 16:17:21 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*help_question_mark(char *str, char *stat_str, int i, int j);
static int	help_redo_expand(char ***exp_vars, int *i, t_data *data);

char	*redo_expand_var(char *str, t_data *data)
{
	char	**exp_vars;
	int		dollars;
	int		i;

	i = 0;
	dollars = count_dollars(str);
	if (dollars == 0)
		return (str);
	exp_vars = ft_split_dollars(str, dollars, 0, 0);
	while (exp_vars[i])
	{
		if (help_redo_expand(&exp_vars, &i, data))
			return (ft_free_array(&exp_vars), g_exit_status = 1, NULL);
		i++;
	}
	str = ft_unsplit(exp_vars);
	ft_free_array(&exp_vars);
	return (str);
}

static int	help_redo_expand(char ***exp_vars, int *i, t_data *data)
{
	char	*tmp;

	if ((*exp_vars)[*i][0] == '"')
	{
		tmp = ft_strtrim((*exp_vars)[*i], "\"");
		if (!tmp)
			return (1);
		free((*exp_vars)[*i]);
		(*exp_vars)[*i] = tmp;
		tmp = redo_expand_var((*exp_vars)[*i], data);
		if (!tmp)
			return (1);
		free((*exp_vars[*i]));
		(*exp_vars)[*i] = tmp;
	}
	if ((*exp_vars)[*i][0] == '$')
	{
		tmp = expand_var_value((*exp_vars)[*i], data);
		if (!tmp)
			return (1);
		free((*exp_vars)[*i]);
		(*exp_vars)[*i] = tmp;
	}
	return (0);
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

char	*question_mark(char *str)
{
	char	*temp;
	char	*stat_str;
	int		i;

	i = 0;
	stat_str = ft_itoa(g_exit_status);
	if (str[i] == '?' && !str[i + 1])
		return (stat_str);
	else
	{
		temp = help_question_mark(str, stat_str, 0, 0);
		if (!temp)
			return (NULL);
	}
	return (temp);
}

static char	*help_question_mark(char *str, char *stat_str, int i, int j)
{
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(ft_strlen(str) + ft_strlen(stat_str), sizeof(char));
	if (!tmp)
		return (g_exit_status = 1, NULL);
	while (str[i])
	{
		if (str[i] == '?')
		{
			while (stat_str[j])
			{
				tmp[j] = stat_str[j];
				j++;
			}
		}
		else
			tmp[j++] = str[i];
		i++;
	}
	tmp[j] = 0;
	return (tmp);
}