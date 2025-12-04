/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:33:48 by strieste          #+#    #+#             */
/*   Updated: 2025/11/24 12:46:48 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char *str)
{
	size_t	count;
	size_t	len;
	char	*final;

	if (!dest)
		return (ft_strdup(str));
	count = 0;
	len = ft_strlen(dest);
	len += ft_strlen(str);
	final = malloc((len + 1) * sizeof(char));
	if (!final)
		return (NULL);
	while (dest[count])
	{
		final[count] = dest[count];
		count++;
	}
	len = 0;
	while (str[len])
		final[count++] = str[len++];
	final[count] = '\0';
	free(dest);
	return (final);
}
