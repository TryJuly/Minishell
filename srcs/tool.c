/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 08:42:45 by strieste          #+#    #+#             */
/*   Updated: 2025/12/22 08:55:15 by strieste         ###   ########.fr       */
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
