/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 19:18:16 by strieste          #+#    #+#             */
/*   Updated: 2026/01/23 11:26:03 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char *replace_var(char *str, int pos, t_data *data);
static char *join_three_parts(char *str, int pos, int key_len, char *value);

int	replace_var_value(t_data *data)
{
	int	    i;
    char    *tmp;
	t_cmd	*current;

	i = 0;
	current = data->cmd_lst;
	while (current)
	{
		i = 0;
		while (current->args[i] && current->args)
		{
			if (i > 0 && ft_strncmp(current->args[i - 1], "<<", 3) == 0)
			{
				i++;
				continue ;
			}
			current->args[i] = expand_token(current->args[i], data);
			tmp = remove_quote(current->args[i]);
        	if (!tmp)
				return (error_malloc(), 1);
			free(current->args[i]);
			current->args[i] = tmp;
			i++;
		}
		current = current->next;
	}
	return (0);
}

char *expand_token(char *str, t_data *data)
{
    int     i;
    char    quote;
	char	*tmp;
	char	*new;

    i = 0;
    quote = 0;
    while (str[i])
    {
        if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
            quote = str[i];
        else if (str[i] == quote)
            quote = 0;
        if (str[i] == '$' && quote != '\'')
        {
			if ((str[i + 1] == '\'' || str[i + 1] == '\"') && quote == 0)
			{
				new = join_three_parts(str, i, 0, "");
				free(str);
				str = new;
				continue ;
			}
			if (str[i + 1] == '?' || ft_isalnum(str[i + 1]) || str[i + 1] == '_')
			{
            	tmp = replace_var(str, i, data);
				free(str);
				str = tmp;
            	continue;
			}
        }
        i++;
    }
    return (str);
}

static char *replace_var(char *str, int pos, t_data *data)
{
    char    *var_name;
    char    *var_value;
    char    *new_str;
    int     key_len;

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

static char *join_three_parts(char *str, int pos, int key_len, char *value)
{
    char *prefix;
    char *suffix;
    char *tmp;
    char *result;

    if (!value)
        value = "";
    prefix = ft_substr(str, 0, pos);
    suffix = ft_strdup(str + pos + 1 + key_len);
    tmp = ft_strjoin(prefix, value);
    result = ft_strjoin(tmp, suffix);
    free(prefix);
    free(suffix);
    free(tmp);
    return (result);
}


char	*get_env_value(char *var_name, t_data *data)
{
    int		i;
	int		name_len;

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

// char *expand_token(char *str, t_data *data)
// {
//     int     i;
//     char    quote;
// 	char	*tmp;

//     i = 0;
//     quote = 0;
//     while (str[i])
//     {
//         if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
//             quote = str[i];
//         else if (str[i] == quote)
//             quote = 0;
//         if (str[i] == '$' && quote != '\'')
//         {
// 			if (str[i + 1] != '\0' && (ft_isalnum(str[i + 1])
// 				|| str[i + 1] == '_' || str[i + 1] == '?'))
// 			{
//             	tmp = replace_var(str, i, data);
// 				free(str);
// 				str = tmp;
//             	continue;
// 			}
//         }
//         i++;
//     }
//     return (str);
// }
