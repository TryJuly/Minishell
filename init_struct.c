/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 08:27:08 by strieste          #+#    #+#             */
/*   Updated: 2025/12/09 11:25:20 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**get_envpath(char **envp);

char	**copy_envp(char **envp)
{
	char	**new_envp;
	int		i;

	new_envp = malloc(sizeof(char *) * (arr_size(envp) + 1));
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

int	init_struct(t_data *data, char **envp)
{
	data->envp = copy_envp(envp);
	data->path = get_envpath(envp);
	if (!data->path)
		return (printf("Error PATH\n"), 1);
	return (0);
}

/*		Malloc array before Use				*/
int	struct_set(t_data *data)
{
	data->cmd = malloc(sizeof(char **));
	data->arg = malloc(sizeof(char **));
	data->envp = NULL;
	data->path = NULL;
	data->infile = 0;
	data->outfile = 0;
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
