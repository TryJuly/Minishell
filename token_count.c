/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 11:13:55 by strieste          #+#    #+#             */
/*   Updated: 2025/12/08 09:03:30 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	end_quote(char *input, char quote);

size_t	token_count(char *s)
{
	size_t	count;
	size_t	len;

	count = 0;
	len = 0;
	while (s[len])
	{
		while (s[len] == ' ')
			len++;
		if (!s[len])
			break ;
		if (op_check(s[len], s[len + 1]) > 0)
		{
			count++;
			len += op_check(s[len], s[len + 1]);
			continue ;
		}
		count++;
		if (s[len] == '"' || s[len] == '\'')
			len += end_quote(&s[len], s[len]);
		else
			while (s[len] && s[len] != 32 && op_check(s[len], s[len + 1]) == 0)
				len++;
	}
	return (count);
}

static int	end_quote(char *input, char quote)
{
	size_t	count;

	count = 1;
	while (input[count] && input[count] != quote)
		count++;
	if (input[count] == quote)
		count++;
	return (count);
}

int	op_check(char c, char next)
{
	if (c == '>' && next == '>')
		return (2);
	if (c == '<' && next == '<')
		return (2);
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}
