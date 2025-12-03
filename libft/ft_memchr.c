/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:30:08 by cbezenco          #+#    #+#             */
/*   Updated: 2025/10/07 14:49:34 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	void			*ptr;
	unsigned char	temp;

	i = 0;
	while (i < n)
	{
		temp = ((unsigned char *)s)[i];
		if (temp == (unsigned char)c)
		{
			ptr = (void *)&s[i];
			return (ptr);
		}
		i++;
	}
	return (NULL);
}
