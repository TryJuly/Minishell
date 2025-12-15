/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 08:11:07 by strieste          #+#    #+#             */
/*   Updated: 2025/12/09 13:30:05 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	end_quote(char *input, char quote, char **str);
static int	operator(char c, char next, char **str);
static int	copy_word(char *input, char **str);
static char	*dup_char(char c);

char	**token_array(char *s)
{
	char	**array;

	array = malloc ((token_count(s) + 1) * sizeof(char**));
	if (!array)
		return (printf("%sError token_array%s\n", RED, NC), NULL);
	if (tokenizer(s, array))
		return (NULL);
	return (array);
}

int	tokenizer(char *s, char **array)
{
	ssize_t	len;
	size_t	count;

	len = 0;
	count = 0;
	while (s[len])
	{
		while (s[len] == 32 && len != -1)
			len++;
		if (!s[len])
			break ;
		if (op_check(s[len], s[len + 1]) > 0 && len != -1)
		{
			len += operator(s[len], s[len + 1], &(array)[count++]);
			continue ;
		}
		if ((s[len] == '"' || s[len] == '\'') && len != -1)
			len += end_quote(&s[len], s[len], &(array)[count++]);
		else
			len += copy_word(&s[len], &(array)[count++]);
		if (len == -1)
			return (printf("%sError malloc tokenizer%s\n", RED, NC), 1);
	}
	array[count] = 0;
	return (0);
}

static int	copy_word(char *s, char **str)
{
	size_t	len;
	size_t	save;

	len = 0;
	save = 0;
	if (s[len] && s[len] != 32 && !op_check(s[len], s[len + 1]))
	{
		while (s[len] && s[len] != 32 && op_check(s[len], s[len + 1]) == 0)
			len++;
		*str = malloc((len + 1) * sizeof(char*));
		if (!(*str))
			return (-1);
		while (save < len)
		{
			(*str)[save] = s[save];
			save++;
		}
		(*str)[save] = '\0';
		return (len);
	}
	return (0);
}

static int	end_quote(char *input, char quote, char **str)
{
	size_t	count;
	size_t	save;

	count = 1;
	save = 0;
	while (input[count] && input[count] != quote)
		count++;
	if (input[count] == quote)
		count++;
	(*str) = malloc((count + 1) * sizeof(char*));
	if (!(*str))
		return (-1);
	while (save < count)
	{
		(*str)[save] = input[save];
		save++;
	}
	(*str)[save] = '\0';
	return (count);
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

static char	*dup_char(char c)
{
	char	*str;

	str = malloc(2 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

// char	**tokenizer(char *s)
// {
// 	char	**array;
// 	ssize_t	len;
// 	size_t	count;
	
// 	len = 0;
// 	count = 0;
// 	array = malloc((token_count(s) + 1) * sizeof(char**));
// 	if (!array)
// 		return (printf("%sError Tokenizer malloc_arr%s\n", RED, NC), NULL);
// 	while (s[len])
// 	{
// 		while (s[len] == 32 && len != -1)
// 			len++;
// 		if (!s[len])
// 			break ;
// 		if (op_check(s[len], s[len + 1]) > 0 && len != -1)
// 		{
// 			len += operator(s[len], s[len + 1], &(array)[count++]);
// 			continue ;
// 		}
// 		if ((s[len] == '"' || s[len] == '\'') && len != -1)
// 			len += end_quote(&s[len], s[len], &(array)[count++]);
// 		else if (s[len] && s[len] != 32 && !op_check(s[len], s[len + 1]) && len != -1)
// 			len += copy_word(&s[len], &(array)[count++]);
// 		if (len == -1)
// 			return (printf("%sError malloc tokenizer%s\n", RED, NC), NULL);
// 	}
// 	array[count] = 0;
// 	return (array);
// }