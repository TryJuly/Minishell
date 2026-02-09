/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:22:03 by cbezenco          #+#    #+#             */
/*   Updated: 2025/10/07 14:50:42 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s[i])
	{
		if (s[i] == ((char)c))
		{
			ptr = (char *)&s[i];
			return (ptr);
		}
		i++;
	}
	if (s[i] == ((char)c))
		return ((char *)&s[i]);
	return ((char *)0);
}
