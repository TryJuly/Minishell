/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 08:11:07 by strieste          #+#    #+#             */
/*   Updated: 2026/01/29 11:58:46 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	tokenizer(char *s, char **array);
static int	operator(char c, char next, char **str);
static int	fill_array(char *s, char **array, int *len);

char	**token_array(char *s)
{
	char	**array;
	int		lenght;

	lenght = token_count(s);
	array = ft_calloc((lenght + 1), sizeof(char *));
	if (!array)
		return (error_malloc(), NULL);
	if (tokenizer(s, array))
		return (NULL);
	return (array);
}

static int	tokenizer(char *s, char **array)
{
	int		len;
	size_t	count;

	len = 0;
	count = 0;
	while (s[len])
	{
		while (s[len] == 32)
			len++;
		if (!s[len])
			break ;
		if (fill_array(s, &array[count++], &len) == -1)
			return (1);
	}
	array[count] = NULL;
	return (0);
}

static int	fill_array(char *s, char **array, int *len)
{
	int	res;

	if (op_check(s[*len], s[*len + 1]) > 0)
	{
		res = operator(s[*len], s[*len + 1], array);
		*len += res;
	}
	else
	{
		res = copy_word(&s[*len], array);
		if (res == -1)
			return (1);
		if (res == 0)
			(*len)++;
		else
			(*len) += res;
	}
	return (0);
}

static int	operator(char c, char next, char **str)
{
	if (c == '>' && next == '>')
	{
		*str = ft_strdup(">>");
		if (!*str)
			return (-1);
		return (2);
	}
	if (c == '<' && next == '<')
	{
		*str = ft_strdup("<<");
		if (!*str)
			return (-1);
		return (2);
	}
	if (c == '<' || c == '>' || c == '|')
	{
		*str = dup_char(c);
		if (!*str)
			return (-1);
		return (1);
	}
	return (0);
}
