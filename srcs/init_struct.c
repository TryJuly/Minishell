/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 08:27:08 by strieste          #+#    #+#             */
/*   Updated: 2026/01/23 12:51:55 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	**copy_envp_struct(char **envp);
static int	find_pos_path(char **envp);

int	init_struct(t_data *data, char **envp)
{
	data->envp = copy_envp_struct(envp);
	data->cmd_lst = 0;
	data->heredoc = 0;
	data->path = NULL;
	return (0);
}

static char	**copy_envp_struct(char **envp)
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

int	get_cmdpath(t_data **data, char **envp)
{
	ssize_t	count;
	char	*first;

	count = 0;
	if (!envp)
		return (1);
	count = find_pos_path(envp);
	if (count == -1)
		return (1);
	if ((*data)->path != NULL)
		ft_free_array(&(*data)->path);
	(*data)->path = ft_split(envp[count], ':');
	if (!(*data)->path)
		return (error_malloc(), 1);
	first = ft_substr((*data)->path[0], 5, ft_strlen((*data)->path[0]));
	if (!first)
		return (ft_free_array(&(*data)->path), 1);
	free((*data)->path[0]);
	(*data)->path[0] = first;
	return (0);
}

static int	find_pos_path(char **envp)
{
	size_t	len;

	len = 0;
	while (envp[len])
	{
		if (!ft_strncmp(envp[len], "PATH=", 5))
			return (len);
		len++;
	}
	return (-1);
}

// int	clean_space(char ***array)
// {
// 	size_t	len;
// 	char	*str;

// 	if (!array || !(*array))
// 		return (ft_putstr_fd("Msh: Error clean_cmd_brut\n", 2), 1);
// 	len = 0;
// 	while ((*array)[len])
// 	{
// 		str = ft_strtrim((*array)[len], " ");
// 		if (!str)
// 			return (ft_putstr_fd("Msh: Error clean_cmd_but%s\n", 2), 1);
// 		free((*array)[len]);
// 		(*array)[len] = str;
// 		len++;
// 	}
// 	return (0);
// }
