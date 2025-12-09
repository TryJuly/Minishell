/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 08:38:46 by strieste          #+#    #+#             */
/*   Updated: 2025/12/09 11:48:32 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


int	ft_free_struct(t_data *data)
{
	if (data->cmd)
		ft_free_array(data->cmd);
	if (data->path)
		ft_free_array(data->path);
	return (0);
}

void	ft_free_array(char **array)
{
	size_t	count;
	size_t	len;

	count = 0;
	while (array[count])
	{
		len = 0;
		while (array[count][len])
			array[count][len++] = 0;
		free(array[count]);
		count++;
	}
	free(array);
	return ;
}
