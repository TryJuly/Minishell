/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:34:26 by cbezenco          #+#    #+#             */
/*   Updated: 2025/10/07 14:49:55 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*temp;
	size_t		i;

	i = 0;
	if (!dest && !src)
		return (dest);
	temp = (char *)src;
	if (dest <= src)
	{
		while (i < n)
		{
			((char *)dest)[i] = temp[i];
			i++;
		}
	}
	else if (dest > src)
	{
		while (n--)
			((char *)dest)[n] = temp[n];
	}
	return (dest);
}
