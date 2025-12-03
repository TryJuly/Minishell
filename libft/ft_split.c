/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:43:10 by cbezenco          #+#    #+#             */
/*   Updated: 2025/10/07 14:50:37 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sep_c(const char *s, char c)
{
	int	i;
	int	count;
	int	x;

	i = 0;
	count = 0;
	x = 0;
	while (s[i])
	{
		if (s[i] != c && x == 0)
		{
			x = 1;
			count++;
		}
		else if (s[i] == c)
			x = 0;
		i++;
	}
	return (count);
}

static void	create_arr(char **arr, const char *s, char c)
{
	char			*ptr;
	size_t			i;
	unsigned int	start;
	int				arr_i;

	i = 0;
	arr_i = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			start = i;
			while ((s[i] != c && i < ft_strlen(s)))
				i++;
			ptr = ft_substr(s, start, i - start);
			arr[arr_i++] = ptr;
		}
		i++;
	}
	arr[arr_i] = NULL;
}

char	**ft_split(const char *s, char c)
{
	char			**arr;

	if (!s)
		return (0);
	arr = (char **)malloc((sep_c(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	create_arr(arr, s, c);
	return (arr);
}
