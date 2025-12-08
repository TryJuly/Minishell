/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:12:13 by strieste          #+#    #+#             */
/*   Updated: 2025/12/08 14:57:49 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	validator(char **array)
{
	if (file_check(array))
		return (1);
}

int	file_check(char **array)
{
	size_t	count;
	size_t	len;

	len = 0;
	while (array[len])
	{
		count = 0;
		
	}
}