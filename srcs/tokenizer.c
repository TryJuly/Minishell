/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 08:11:07 by strieste          #+#    #+#             */
/*   Updated: 2026/01/23 13:09:55 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	copy_word(char *input, char **str);
static int	operator(char c, char next, char **str);
// static int	redir_end_line(char **array);
static int tokenizer(char *s, char **array);
static int	help_copy(char *s);

char	**token_array(char *s)
{
	char	**array;

	array = malloc((token_count(s) + 1) * sizeof(char **));
	if (!array)
		return (ft_putstr_fd("Msh: Error Malloc\n", 2), NULL);
	if (tokenizer(s, array))
		return (NULL);
	// if (redir_end_line(array))
	// {
	// 	free_classic(array);
	// 	ft_putstr_fd("Msh: syntax error near unexpected token `newline'\n", 2);
	// 	return (NULL);
	// }
	return (array);
}

static int tokenizer(char *s, char **array)
{
    int len; // Utilise un int pour pouvoir checker le -1 de copy_word
    size_t  count;
    int     res;

    len = 0;
    count = 0;
    while (s[len])
    {
        while (s[len] == 32)
            len++;
        if (!s[len])
            break ;
        if (op_check(s[len], s[len + 1]) > 0)
        {
            res = operator(s[len], s[len + 1], &(array)[count++]);
            len += res;
        }
        else
        {
            res = copy_word(&s[len], &(array)[count++]);
            if (res == -1)
                return (error_malloc(), 1);
            if (res == 0)
                len++;
            else
                len += res;
        }
    }
    array[count] = NULL;
    return (0);
}

static int  copy_word(char *s, char **str)
{
    size_t  len;
    size_t  save;

    save = 0;
    len = help_copy(s);
    *str = malloc((len + 1) * sizeof(char));
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

static int	help_copy(char *s)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != 32 && !op_check(s[len], s[len + 1]))
	{
		if (s[len] == '\'' || s[len] == '"')
			len += ending_quote(&s[len], s[len]);
		else
			len++;
	}
	return (len);
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

// static int	redir_end_line(char **array)
// {
// 	size_t	len;

// 	len = 0;
// 	while (array[len])
// 	{
// 		if (array[len][0] == '>')
// 			if (!array[len + 1])
// 				return (1);
// 		len++;
// 	}
// 	return (0);
// }

// int	tokenizer(char *s, char **array)
// {
// 	ssize_t	len;
// 	size_t	count;

// 	len = 0;
// 	count = 0;
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
// 		else
// 			len += copy_word(&s[len], &(array)[count++]);
// 		if (len == -1)
// 			return (ft_putstr_fd("Msh: Error malloc\n", 2), 1);
// 	}
// 	array[count] = 0;
// 	return (0);
// }

// static int	copy_word(char *s, char **str)
// {
// 	size_t	len;
// 	size_t	save;

// 	len = 0;
// 	save = 0;
// 	if (s[len] && s[len] != 32 && !op_check(s[len], s[len + 1]))
// 	{
// 		len = help_copy(s);
// 		*str = malloc((len + 1) * sizeof(char *));
// 		if (!(*str))
// 			return (-1);
// 		while (save < len)
// 		{
// 			(*str)[save] = s[save];
// 			save++;
// 		}
// 		(*str)[save] = '\0';
// 		return (len);
// 	}
// 	return (0);
// }

// static int	end_quot(char *input, char quote)
// {
// 	size_t	count;

// 	count = 1;
// 	while (input[count] && input[count] != quote)
// 		count++;
// 	if (input[count] == quote)
// 		count++;
// 	return (count);
// }

// static int	copy_word(char *s, char **str)
// {
// 	size_t	len;
// 	size_t	save;

// 	len = 0;
// 	save = 0;
// 	if (s[len] && s[len] != 32 && !op_check(s[len], s[len + 1]))
// 	{
// 		while (s[len] && s[len] != 32 && op_check(s[len], s[len + 1]) == 0)
// 			len++;
// 		*str = malloc((len + 1) * sizeof(char *));
// 		if (!(*str))
// 			return (-1);
// 		while (save < len)
// 		{
// 			(*str)[save] = s[save];
// 			save++;
// 		}
// 		(*str)[save] = '\0';
// 		return (len);
// 	}
// 	return (0);
// }

// static int	end_quote(char *input, char quote, char **str)
// {
// 	size_t	count;
// 	size_t	save;

// 	count = 1;
// 	save = 0;
// 	while (input[count] && input[count] != quote)
// 		count++;
// 	if (input[count] == quote)
// 		count++;
// 	(*str) = malloc((count + 1) * sizeof(char));
// 	if (!(*str))
// 		return (-1);
// 	while (save < count)
// 	{
// 		(*str)[save] = input[save];
// 		save++;
// 	}
// 	(*str)[save] = '\0';
// 	return (count);
// }
