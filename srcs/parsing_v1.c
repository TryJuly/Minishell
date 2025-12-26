/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_v1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:58:59 by strieste          #+#    #+#             */
/*   Updated: 2025/12/26 10:06:54 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	find_path_1(char **cmd, char **path)
{
	size_t	count;
	char	*command;

	command = NULL;
	count = 0;
	if (!path || !*path)
		return (1);
	while (path[count])
	{
		command = ft_strcat(command, path[count]);
		command = ft_strcat(command, "/");
		command = ft_strcat(command, *cmd);
		if (!access(command, F_OK) && !access(command, X_OK))
		{
			free(*cmd);
			*cmd = command;
			return (0);
		}
		free(command);
		command = NULL;
		count++;
	}
	return (1);
}
