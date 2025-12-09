/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:12:13 by strieste          #+#    #+#             */
/*   Updated: 2025/12/09 13:31:10 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	is_operator(char *str);

// static int	file_validator(char **array);
// static int	pipe_validator(char **array);
static int	quote_validator(char *str, int quote);

int	validator(char **array)
{
	size_t	len;

	len = 0;
	while (array[len])
	{
		if (is_operator(array[len]))
			if (is_operator(array[len + 1]))
				return (1);
		if (array[len][0] == '"' || array[len][0] == '\'')
			if (quote_validator(array[len], array[len][0]))
				return (1);
		len++;
	}
	return (0);
}

static int	is_operator(char *str)
{
	if (str[0] == '|')
		return (1);
	if (str[0] == '<')
		return (1);
	if (str[0] == '>')
		return (1);
	return (0);
}

// static int	file_validator(char **array)
// {
// 	size_t	count;
// 	size_t	len;

// 	len = 0;
// 	while (array[len])
// 	{
// 		if (array[len] == '<')
// 		{
// 			len++;
// 			if (access(array[len], F_OK))
// 				return (printf("%szsh: no such file or directory: %s%s\n", RED, array[len], NC), 1);
// 			if (access(array[len], R_OK))
// 				return (printf("%szsh: permission denied: %s%s\n", RED, array[len], NC), 1);
// 		}
// 		len++;
// 	}
// 	return (0);
// }

// static int	pipe_validator(char **array)
// {
// 	size_t	count;
	
// 	if (array[0][0] == '|')
// 		return (printf("%szsh: parse error near |%s\n", RED, NC), 1);
// 	count = 0;
// 	while (array[count])
// 	{
// 		if (array[count][0] == '|' && array[count + 1][0] == '|')
// 			return (printf("%sError double PIPE%s\n", RED, NC), 1);
// 		count++;
// 	}
// 	return (0);
// }

static int	quote_validator(char *str, int quote)
{
	size_t	len;

	len = ft_strlen(str) - 1;
		if (str[len] != quote)
			return (printf("%sQuote no closed%s\n", RED, NC), 1);
	return (0);
}
