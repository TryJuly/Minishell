/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 11:29:26 by strieste          #+#    #+#             */
/*   Updated: 2026/01/23 13:11:19 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
