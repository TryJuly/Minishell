/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_v1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:56:42 by cbezenco          #+#    #+#             */
/*   Updated: 2026/01/05 15:57:42 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	help_other_split(char *str, int *i, int *j)
{
	int		par;

	par = 0;
	*j = *i + 1;
	if (str[*j] == '(')
		par = 1;
	while ((str[*j] != '$' && (str[*j] != ' ' || par == 1)
			&& str[*j] != '\'' && str[*j] != '"' && str[*j]))
	{
		if (str[*j] == ')')
			par = 0;
		*j += 1;
	}
}

char	**other_ft_split_dollars(char *str, int dollars)
{
	int		i;
	int		j;
	int		res_i;
	char	**res;
	char	*temp;

	i = 0;
	res_i = 0;
	res = malloc(sizeof(char *) * (dollars + 3));
	while (str[i])
	{
		if (str[i] == '$')
			help_other_split(str, &i, &j);
		else
		{
			j = i + 1;
			while (str[j] != '$' && str[j])
				j++;
		}
		temp = ft_substr(str, i, j - i);
		res[res_i++] = temp;
		i = j;
	}
	res[res_i] = NULL;
	return (res);
}
