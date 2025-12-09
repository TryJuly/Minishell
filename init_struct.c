/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 08:27:08 by strieste          #+#    #+#             */
/*   Updated: 2025/12/08 08:22:06 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	get_cmdpath(t_data *data, char **envp);
int	copy_envp(t_data *data, char **envp);

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

int	copy_envp(t_data *data, char **envp)
{
	data->cmd = malloc(sizeof(char **));
	data->arg = malloc(sizeof(char **));
	data->envp = NULL;
	data->path = NULL;
	data->infile = 0;
	data->outfile = 0;
	return (0);
}

int	get_cmdpath(t_data *data, char **envp)
{
	size_t	count;
	char	*first;

	count = 0;
	if (!data->env)
		return (1);
	while (ft_strncmp(envp[count], "PATH=", 5))
		count++;
	data->path = ft_split(envp[count], ':');
	if (!data->path)
		return (printf("%sError split_envpath%s\n", RED, NC), 1);
	first = ft_substr(data->path[0], 5, ft_strlen(data->path[0]));
	if (!first)
		return (ft_free_array(&data->path), 1);
	free(data->path[0]);
	data->path[0] = first;
	return (0);
}

int	clean_space(char ***array)
{
	size_t	len;
	char	*str;

	if (!array || !(*array))
		return (printf("%sError clean_cmd_brut%s\n", RED, NC), 1);
	len = 0;
	while ((*array)[len])
	{
		str = ft_strtrim((*array)[len], " ");
		if (!str)
			return (printf("%sError clean_cmd_but%s\n", RED, NC), 1);
		free((*array)[len]);
		(*array)[len] = str;
		len++;
	}
	return (0);
}
