/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:28:17 by cbezenco          #+#    #+#             */
/*   Updated: 2025/10/07 14:49:40 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	c_s1;
	unsigned char	c_s2;

	i = 0;
	if (n <= 0)
		return (0);
	while (i < n)
	{
		c_s1 = ((unsigned char *)s1)[i];
		c_s2 = ((unsigned char *)s2)[i];
		if (c_s1 != c_s2)
			return (c_s1 - c_s2);
		i++;
	}
	return (0);
}
