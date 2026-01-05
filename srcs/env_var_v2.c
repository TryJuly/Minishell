/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:12:29 by strieste          #+#    #+#             */
/*   Updated: 2026/01/05 15:21:59 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*add_quote(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 1;
	res = malloc((ft_strlen(str) + 3) * sizeof(char));
	if (!res)
		return (NULL);
	res[0] = '"';
	while (str[i])
		res[j++] = str[i++];
	res[j++] = '"';
	res[j++] = '\0';
	return (res);
}

int	no_dollars(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
