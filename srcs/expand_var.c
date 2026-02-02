/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 19:18:16 by strieste          #+#    #+#             */
/*   Updated: 2026/01/29 12:26:04 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*replace_var(char *str, int pos, t_data *data);
static char	*handle_expand(char *str, int *i, t_data *data, char quote);
static char	*join_three_parts(char *str, int pos, int key_len, char *value);

char	*expand_token(char *str, t_data *data)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
			quote = str[i++];
		else if (str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else if (str[i] == '$' && quote != '\'')
			str = handle_expand(str, &i, data, quote);
		else
			i++;
	}
	return (str);
}

static char	*handle_expand(char *str, int *i, t_data *data, char quote)
{
	char	*new;

	if ((str[*i + 1] == '\'' || str[*i + 1] == '\"') && quote == 0)
	{
		new = join_three_parts(str, *i, 0, "");
		free(str);
		return (new);
	}
	if (str[*i + 1] == '?' || ft_isalnum(str[*i + 1]) || str[*i + 1] == '_')
	{
		new = replace_var(str, *i, data);
		free(str);
		return (new);
	}
	(*i)++;
	return (str);
}

static char	*replace_var(char *str, int pos, t_data *data)
{
	char	*var_name;
	char	*var_value;
	char	*new_str;
	int		key_len;

	key_len = 0;
	if (str[pos + 1] == '\0' || (!ft_isalnum(str[pos + 1])
			&& str[pos + 1] != '_' && str[pos + 1] != '?'))
	{
		return (ft_strdup(str));
	}
	if (str[pos + 1] == '?')
		key_len = 1;
	else
	{
		while (str[pos + 1 + key_len] && (ft_isalnum(str[pos + 1 + key_len])
				|| str[pos + 1 + key_len] == '_'))
			key_len++;
	}
	var_name = ft_substr(str, pos + 1, key_len);
	var_value = get_env_value(var_name, data);
	free(var_name);
	new_str = join_three_parts(str, pos, key_len, var_value);
	free(var_value);
	return (new_str);
}

static char	*join_three_parts(char *str, int pos, int key_len, char *value)
{
	char	*prefix;
	char	*suffix;
	char	*tmp;
	char	*result;

	if (!value)
		value = "";
	prefix = ft_substr(str, 0, pos);
	if (!prefix)
		return (NULL);
	suffix = ft_strdup(str + pos + 1 + key_len);
	if (!suffix)
		return (free(prefix), NULL);
	tmp = ft_strjoin(prefix, value);
	result = ft_strjoin(tmp, suffix);
	free(prefix);
	free(suffix);
	free(tmp);
	return (result);
}
