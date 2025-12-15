/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:12:13 by strieste          #+#    #+#             */
/*   Updated: 2025/12/10 15:04:52 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	redir_check(char *str);
static int	quote_check(char *str);
static int	pipe_check(char *str);
static int	is_out_check(char *str);
static int	is_operator(char c);

int	input_brute(char *str)
{
	size_t	count;

	count = 0;
	while (str[count] == ' ')
		count++;
	if (pipe_check(&str[count]))
		return (1);
	if (redir_check(&str[count]))
		return (1);
	if (quote_check(&str[count]))
		return (printf("%sUnclosed Quotes%s\n", RED, NC), 1);
	if (is_out_check(&str[count]))
		return (1);
	return (0);
}

static int	pipe_check(char *str)
{
	size_t	count;
	int		quote;

	if (str[0] == '|' && (str[1] || !str[1]))
		return (printf("%szsh: parse error near `|'%s\n", RED, NC), 1);
	if (str[0] == '|' && str[1] == '|')
		return (printf("%szsh: parse error near `||'%s\n", RED, NC), 1);
	count = 0;
	quote = 0;
	while (str[count])
	{
		if ((str[count] == '\'' || str[count] == '"') && !quote)
			quote = str[count++];
		if ((str[count] == '\'' || str[count] == '"') && quote)
			quote = 0;
		if (str[count] == '|' && is_operator(str[count - 1]))
			return (printf("%szsh: parse error near `|'%s\n", RED, NC), 1);
		if (str[count] == '|' && is_operator(str[count + 1]))
			return (printf("%szsh: parse error near `|'%s\n", RED, NC), 1);
		if (str[count] == '|' && str[count + 1] == '|' && !quote)
			return (printf("%sMinishell not taking || input%s\n", RED, NC), 1);
		count++;
	}
	return (0);
}

static int	is_operator(char c)
{
	if (c == '|')
		return (1);
	if (c == '<' || c == '>')
		return (1);
	if (c == '|')
		return (1);
	return (0);
}

static int	redir_check(char *str)
{
	size_t	count;
	int		quote;

	count = 0;
	quote = 0;
	if (str[0] == 60 && str[1] == 60 && str[2] == 60 && str[3] == '\0')	// 60 = '<'
			return (printf("%szsh: parse error near `\\n'%s\n", RED, NC), 1);
	while (str[count])
	{
		if ((str[count] == '\'' || str[count] == '"') && !quote)
			quote = str[count++];
		if ((str[count] == '\'' || str[count] == '"') && quote)
			quote = 0;
		if (str[count] && !quote)
		{
			if (str[count] == 62 && str[count + 1] == 62 && str[count + 2] == 62)	// 62 = '>'
				return (printf("%szsh: parse error near `>'%s\n", RED, NC), 1);
			// if (str[count] == 60 && str[count + 1] == 62)
			// 	return (printf("%sError redir \"<>\"%s\n", RED, NC), 1);
			if (str[count] == 62 && str[count + 1] == 60)
				return (printf("%szsh: parse error near `<'%s\n", RED, NC), 1);
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
				return (1);
			if (str[count] && str[count] == quote)
				quote = 0;
		}
		count++;
	}
	return (0);
}

static int	is_out_check(char *str)
{
	size_t	count;
	int		quote;

	count = 0;
	quote = 0;
	while (str[count])
	{
		if ((str[count] == '\'' || str[count] == '"') && !quote)
			quote = str[count++];
		if ((str[count] == '\'' || str[count] == '"') && quote)
			quote = 0;
		if (str[count] == ';' && !quote)
			return (printf("%sMinishell not taking ; input%s\n", RED, NC), 1);
		if (str[count] == '&' && !quote)
			return (printf("%sMinishell not taking & input%s\n", RED, NC), 1);
		if ((str[count] == '(' || str[count] == ')') && !quote)
			return (printf("%sMinishell not taking () input%s\n", RED, NC), 1);
		if (str[count] == '\\' && !quote)
			return (printf("%sMinishell not taking \\ input%s\n", RED, NC), 1);
		if (str[count] == '*' && !quote)
			return (printf("%sMinishell not taking * input%s\n", RED, NC), 1);
		count++;
	}
	return (0);
}
