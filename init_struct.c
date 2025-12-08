/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 08:27:08 by strieste          #+#    #+#             */
/*   Updated: 2025/12/08 08:22:06 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	get_cmdpath(t_data *data, char **envp);
int	copy_envp(t_data *data, char **envp);

int	init_struct(t_data *data, char **envp)
{
	copy_envp(data, envp);
	get_cmdpath(data, envp);
	return (0);
}

int	copy_envp(t_data *data, char **envp)
{
	size_t	count;

	count = 0;
	while (envp[count])
		count++;
	data->env = malloc((count + 1) * sizeof(char **));
	if (!data->env)
		return (printf("%sError malloc copy_path%s\n", RED, NC), 1);
	count = 0;
	while (envp[count])
	{
		data->env[count] = ft_strdup(envp[count]);
		if (!data->env[count])
		{
			ft_free_array(&data->env);
			return (printf("%sError copy_envp%s\n", RED, NC), 1);
		}
		count++;
	}
	data->env[count] = 0;
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
