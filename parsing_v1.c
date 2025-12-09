/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_v1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:58:59 by strieste          #+#    #+#             */
/*   Updated: 2025/12/08 07:46:46 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*help_function(char *cmd);

char	*find_path(char *cmd, char **path)
{
	size_t	count;
	char	*command;
	
	if (cmd[0] == '/')
		return (help_function(cmd));
	else
	{
		command = NULL;
		count = 0;
		while (path[count])
		{
			command = ft_strcat(command, path[count]);
			command = ft_strcat(command, "/");
			command = ft_strcat(command, cmd);
			if (!access(command, F_OK) && !access(command, X_OK))
				return (command);
			free(command);
			command = NULL;
			count++;
		}
	}
	return (printf("Error acces PATH\n"), NULL);
}

static char	*help_function(char *cmd)
{	
	if (access(cmd, F_OK))
		return (printf("Chemin d'acces commande Invalide\n"), NULL);
	if (access(cmd, R_OK))
		return (printf("Erreur lecture chemin outifle\n"), NULL);
	if (access(cmd, X_OK))
		return (printf("Execution du chemin impossible\n"), NULL);
	if (!cmd)
		return (NULL);
	return (ft_strdup(cmd));
}
