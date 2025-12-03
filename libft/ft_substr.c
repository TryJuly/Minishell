/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:56:12 by cbezenco          #+#    #+#             */
/*   Updated: 2025/10/07 14:53:50 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		i;

	i = 0;
	if (!s)
		return (0);
	if (start >= (size_t)ft_strlen(s))
		return (ft_calloc(1, 1));
	if (len > (size_t)ft_strlen(s) - start)
		str = malloc(sizeof(char) * ((size_t)ft_strlen(s) - start + 1));
	else
		str = malloc((sizeof(char)) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len && s[start])
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
