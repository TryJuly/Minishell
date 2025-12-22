/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:12:13 by strieste          #+#    #+#             */
/*   Updated: 2025/12/22 13:33:00 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	redir_check(char *str);
static int	quote_check(char *str);
static int	is_out_check(char *str);
static int	find_heredoc(char *str, t_data *data);

int	input_brute(char *str, t_data *data)
{
	size_t	count;
	int		valide;

	count = 0;
	valide = 0;
	count = skip_space(&str[count]);
	if (str[count] == '|' && str[count + 1] == '|')
		return (printf("%sMsh: syntax error near unexpected token `||'%s\n", RED, NC), 1);
	if (str[count] == '|')
		return (printf("%sMsh: syntax error near unexpected token `|'%s\n", RED, NC), 1);
	if (quote_check(&str[count]))
		valide = 1;
	if (is_out_check(&str[count]))
		valide = 1;
	if (redir_check(&str[count]))
		valide = 1;
	if (find_heredoc(&str[count], data))
		valide = 1;
	if (valide == 1)
		return (1);
	return (0);
}

static int	find_heredoc(char *str, t_data *data)
{
	size_t	count;

	count = 0;
	while (str[count])
	{
		if (str[count] == '<' && str[count + 1] == '<')
		{
			heredoc(&str[count + 2], data);
			count += 2;
		}
		count++;
	}
	return (0);
}

static int	redir_check(char *str)
{
	size_t	len;
	int		quote;

	len = 0;
	quote = 0;
	len += skip_space(str);
	while (str[len])
	{
		if ((str[len] == '\'' || str[len] == '"') && !quote)
			quote = str[len++];
		if ((str[len] == '\'' || str[len] == '"') && quote)
			quote = 0;
		if (str[len] && !quote)
		{
			if (str[len] == 62 && str[len + 1] == 62 && str[len + 2] == 62)
				return (printf("%sMsh: parse error near `>'%s\n", RED, NC), 1);
			if (str[len] == 62 && str[len + 1] == 60)
				return (printf("%sMsh: parse error near `<'%s\n", RED, NC), 1);
		}
		len++;
	}
	return (0);
}

static int	quote_check(char *str)
{
	size_t	count;
	int		quote;

	count = 0;
	quote = 0;
	while (str[count])
	{
		if ((str[count] == '"' || str[count] == '\'') && !quote)
			quote = str[count++];
		if (quote && str[count])
		{
			while (str[count] && str[count] != quote)
				count++;
			if (!str[count])
				return (printf("%sMsh: Unclosed quote `%c'%s\n", RED, quote, NC), 1);
			if (str[count] && str[count] == quote)
				quote = 0;
		}
		count++;
	}
	return (0);
}

static int	is_out_check(char *str)
{
	size_t	len;
	int		quote;

	len = 0;
	quote = 0;
	while (str[len])
	{
		if ((str[len] == '\'' || str[len] == '"') && (!quote))
			quote = str[len++];
		if ((str[len] == '\'' || str[len] == '"') && (quote))
			quote = 0;
		if ((str[len] == ';' || str[len] == '&') && !quote)
			return (printf("%sMsh: not taking %c input%s\n", RED, str[len], NC), 1);
		if ((str[len] == '(' || str[len] == ')') && (!quote))
			return (printf("%sMsh: not taking `()' input%s\n", RED, NC), 1);
		if (str[len] == '\\' && (!quote))
			return (printf("%sMsh: not taking \\ input%s\n", RED, NC), 1);
		if (str[len] == '*' && (!quote))
			return (printf("%sMsh: not taking * input%s\n", RED, NC), 1);
		if (str[len + 1] && str[len] == '|' && str[len + 1] == '|')
			return (printf("%sMsh: not taking || input%s\n", RED, NC), 1);
		len++;
	}
	return (0);
}

// int	check_redir(t_data *data)
// {
// 	size_t	count;
// 	//char	*redir;

// 	count = 0;
// 	while (data->input[count])
// 	{
// 		if (!strncmp(&data->input[count], "<<", 2))
// 		{
// 			count += skip_space(&data->input[count]);
// 			// Is a heredoc
// 		}
// 		if (data->input[count] == '<')
// 		{
// 			count += skip_space(&data->input[count]);
// 		}
// 		count++;
// 	}
// 	return (count);
// }
