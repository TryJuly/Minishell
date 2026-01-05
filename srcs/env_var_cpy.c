/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_cpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:58:16 by cbezenco          #+#    #+#             */
/*   Updated: 2026/01/05 16:17:53 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	help_new_expand(char **tab, char *tmp, t_data *data);
static char	*help_split_dollars(char *s, int *i, int *j);
char		*add_quote(char *str);

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
	exp_vars = ft_split_dollars(data->input, dollars, 0, 0);
	while (exp_vars[i])
	{
		help_new_expand(&exp_vars[i], 0, data);
		i++;
	}
	tmp = ft_unsplit(exp_vars);
	ft_free_array(&exp_vars);
	free(data->input);
	data->input = tmp;
}

static int	help_new_expand(char **tab, char *tmp, t_data *data)
{
	if ((*tab)[0] == '"')
	{
		tmp = ft_strtrim(*tab, "\"");
		if (!tmp)
			return (1);
		free(*tab);
		*tab = redo_expand_var(tmp, data);
		if (!*tab)
			return (1);
		free(tmp);
		tmp = add_quote(*tab);
		if (!tmp)
			return (1);
		free(*tab);
		*tab = tmp;
	}
	if ((*tab)[0] == '$')
	{
		tmp = expand_var_value(*tab, data);
		if (!tmp)
			return (1);
		free(*tab);
		*tab = tmp;
	}
	return (0);
}

char	**ft_split_dollars(char *s, int dollars, int i, int j)
{
	char	**res;
	char	*temp;
	int		res_i;

	i = 0;
	res_i = 0;
	res = ft_calloc((dollars + 1), sizeof(char *));
	while (s[i])
	{
		if ((s[i] == '$') || s[i] == '"' || s[i] == '\'')
			temp = help_split_dollars(s, &i, &j);
		else if (s[i] == ' ')
			temp = blank_space(s, &i, &j);
		else
		{
			j = i + 1;
			while ((s[j] != '$' && s[j] != '\'' && s[j] != '\"') && s[j])
				j++;
			temp = ft_substr(s, i, j - i);
			i = j - 1;
		}
		res[res_i++] = temp;
		i++;
	}
	return (res);
}

static char	*help_split_dollars(char *s, int *i, int *j)
{
	char	*temp;

	*j = *i + 1;
	if (s[*j] == '(')
	{
		while (s[*j] != ')')
			*j += 1;
		*j += 1;
	}
	else if (s[*i] == '\'' || s[*i] == '\"')
		expand_quote(s, i, j);
	else
	{
		while ((s[*j] && s[*j] != '$' && s[*j] != ' ')
			&& (s[*j] != '\'' && s[*j] != '"'))
			*j += 1;
	}
	temp = ft_substr(s, *i, *j - *i);
	*i = *j - 1;
	return (temp);
}