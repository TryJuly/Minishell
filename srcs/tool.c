/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 08:42:45 by strieste          #+#    #+#             */
/*   Updated: 2025/12/22 13:22:25 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	*malloc_pipe(void)
{
	int	*pipe;

	pipe = calloc(2, sizeof(int));
	if (pipe)
		return (printf("%sMsh: malloc pipe fail%s\n", RED, NC), (int*)-1);
	return (pipe);
}

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
