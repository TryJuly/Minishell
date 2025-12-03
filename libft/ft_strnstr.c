/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:44:09 by cbezenco          #+#    #+#             */
/*   Updated: 2025/10/07 14:52:11 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	if (!little && len == 0)
		return ((char *)big);
	if (!big && len == 0)
		return (0);
	if (little[0] == '\0')
		return (((char *)big));
	if (big == little)
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while ((little[j] && big[i]) && (little[j] == big[i]) && i < len)
		{
			j++;
			i++;
		}
		if (little[j] == '\0')
			return (((char *)big) + (i - j));
		i = i - j + 1;
	}
	return (NULL);
}
