/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:03:32 by cbezenco          #+#    #+#             */
/*   Updated: 2025/10/07 14:51:02 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_d;
	size_t	len_s;
	size_t	len_tot;

	if ((!dst || !src) && size == 0)
		return (0);
	i = 0;
	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	len_tot = size - len_d - 1;
	if (size == 0)
		return (len_s);
	if (len_d >= size)
		return (size + len_s);
	while (src[i] && len_tot--)
	{
		dst[len_d + i] = src[i];
		i++;
	}
	dst[len_d + i] = '\0';
	return (len_d + len_s);
}
