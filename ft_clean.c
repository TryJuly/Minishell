/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 08:38:46 by strieste          #+#    #+#             */
/*   Updated: 2025/12/08 13:23:30 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


// int	ft_free_struct(t_data *data)
// {
// 	if (data->cmd)
// 		ft_free_array(data->cmd);
// 	if (data->path)
// 		ft_free_array(data->path);
// 	return (0);
// }

int	ft_free_array(char ***array)
{
	size_t	count;

	if (!array || !(*array))
		return (0);
	count = 0;
	while ((*array)[count])
	{
		free((*array)[count]);
		count++;
	}
	free(*array);
	*array = NULL;
	return (0);
}
