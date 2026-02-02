/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 11:29:26 by strieste          #+#    #+#             */
/*   Updated: 2026/01/29 11:57:52 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	help_copy(char *s);

int	ending_quote(char *s, char quote)
{
	size_t	len;

	len = 0;
	if (s[len] == quote)
		len++;
	while (s[len] && s[len] != quote)
		len++;
	if (s[len] && s[len] == quote)
		len++;
	return (len);
}

char	*dup_char(char c)
{
	char	*str;

	str = malloc(2 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

int	copy_word(char *s, char **str)
{
	size_t	len;
	size_t	save;

	save = 0;
	len = help_copy(s);
	*str = malloc((len + 1) * sizeof(char));
	if (!(*str))
		return (error_malloc(), -1);
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
