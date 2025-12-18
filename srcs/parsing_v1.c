/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_v1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:58:59 by strieste          #+#    #+#             */
/*   Updated: 2025/12/18 14:31:11 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	find_path_1(char **cmd, char **path)
{
	size_t	count;
	char	*command;

	command = NULL;
	count = 0;
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
	return (0);
}
