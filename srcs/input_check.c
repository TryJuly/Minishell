/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:12:13 by strieste          #+#    #+#             */
/*   Updated: 2025/12/22 09:33:51 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	redir_check(char *str);
static int	quote_check(char *str);
// static int	pipe_check(char *str);
static int	is_out_check(char *str);
// static int	is_operator(char c);
static int	skip_space(char *str);
// static int	skip_quote(char *str, int quote);

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
	if (valide)
		return (1);
	return (0);
}

int	check_redir(t_data *data)
{
	size_t	count;
	char	*redir;

	count = 0;
	while (data->input[count])
	{
		if (!strncmp(&data->input[count], "<<", 2))
		{
			count += skip_space(&data->input[count]);
			// Is a heredoc
		}
		if (data->input[count] == '<')
		{
			count += skip_space(&data->input[count]);
			
		}
		count++;
	}
}

static char	*redir_name(char *str)
{
	size_t	count;

	count = 0;
	while (str[count] && ft_isascii(str[count]))
}

static int	skip_space(char *str)
{
	size_t	count;

	count = 0;
	while (str[count] && str[count] == ' ')
		count++;
	return (count);
}

// static int	is_operator(char c)
// {
// 	if (c == '|')
// 		return (1);
// 	if (c == '<' || c == '>')
// 		return (1);
// 	return (0);
// }

static int	redir_check(char *str)
{
	size_t	count;
	int		quote;

	count = 0;
	quote = 0;
	count += skip_space(str);
	while (str[count])
	{
		if ((str[count] == '\'' || str[count] == '"') && !quote)
			quote = str[count++];
		if ((str[count] == '\'' || str[count] == '"') && quote)
			quote = 0;
		if (str[count] && !quote)
		{
			if (str[count] == 62 && str[count + 1] == 62 && str[count + 2] == 62)	// 62 = '>'
				return (printf("%sMsh: parse error near `>'%s\n", RED, NC), 1);
			if (str[count] == 62 && str[count + 1] == 60)
				return (printf("%sMsh: parse error near `<'%s\n", RED, NC), 1);
		}
		count++;
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

// static int	skip_quote(char *str, int quote)
// {
// 	size_t	count;

// 	count = 0;
// 	while (str[count] && str[count] != quote)
// 		count++;
// 	if (!str[count])
// 		return (-1);
// 	return (count);
// }

// static int	pipe_check(char *str)
// {
// 	size_t	count;
// 	int		c;

// 	count = 0;
// 	c = 0;
// 	while (str[count])
// 	{
// 		if ((str[count] == '\'' || str[count] == '"') && !c)
// 		{
// 			c = str[count++];
// 			while (str[count] && str[count] != c)
// 				count++;
// 			if (str[count] && str[count] == c)
// 				c = 0;
// 		}
// 		if (is_operator(str[count]))
// 		{
// 			c = str[count++];
// 			count += skip_space(&str[count]);
// 			if (is_operator(str[count]))
// 			{
// 				count += skip_space(&str[count]);
// 				if (str[count] && str[count] == '|')
// 					return (printf("%sminishell: syntax error near unexpected token `|'%s\n", RED, NC), 1);
// 			}
// 		}
// 		count++;
// 	}
// 	return (0);
// }
