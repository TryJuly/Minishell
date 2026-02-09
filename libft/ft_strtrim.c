/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:20:43 by cbezenco          #+#    #+#             */
/*   Updated: 2025/10/07 14:53:44 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*cpy;
	int		cpy_i;
	size_t	i;
	size_t	j;

	i = 0;
	cpy_i = 0;
	if (!s1 || !set)
		return (0);
	j = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	if (s1[i] == '\0')
		return ((char *)ft_calloc(1, 1));
	while (ft_strchr(set, s1[j - 1]))
		j--;
	cpy = malloc(sizeof(char) * (j - i + 1));
	if (!cpy)
		return (NULL);
	while (i < j)
		cpy[cpy_i++] = s1[i++];
	cpy[cpy_i] = '\0';
	return (cpy);
}
