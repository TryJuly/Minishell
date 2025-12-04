/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 08:27:08 by strieste          #+#    #+#             */
/*   Updated: 2025/12/04 08:44:59 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**get_envpath(char **envp);

int	init_struct(t_data *data, char **envp)
{
	data->envp = envp;
	data->path = get_envpath(envp);
	if (!data->path)
		return (printf("Error PATH\n"), 1);
	return (0);
}

int	struct_set(t_data *data)
{
	data->cmd = NULL;
	data->envp = NULL;
	data->path = NULL;
	data->redir = 0;
	return (0);
}

char	**get_envpath(char **envp)
{
	size_t	count;
	char	**path;
	char	*first;

	count = 0;
	while (ft_strncmp(envp[count], "PATH=", 5))
		count++;
	path = ft_split(envp[count], ':');
	if (!path[0])
		return (printf("Error search PATH\n"), NULL);
	first = ft_substr(path[0], 5, ft_strlen(path[0]));
	if (!first[0])
		return (ft_free_array(path), NULL);
	free(path[0]);
	path[0] = first;
	return (path);
}
