/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:21:05 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/09 15:18:46 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_unset_arg(t_data *data)
{
	int		i;
	int		offset;
	int		envp_size;
	char	**new_envp;

	i = 0;
	offset = 0;
	envp_size = arr_size(data->envp);
	new_envp = malloc((sizeof(char *) * (envp_size - 1)));
	if (!new_envp)
		printf("pas bon");
	while (data->envp[i + offset])
	{
		if (ft_strncmp(data->envp[i + offset],
				data->cmd_lst->args[1], ft_strlen(data->cmd_lst->args[1])) == 0)
		{
			offset += 1;
			continue ;
		}
		new_envp[i] = data->envp[i + offset];
		i++;
	}
	new_envp[i] = NULL;
	free(data->envp);
	data->envp = new_envp;
}

void	ft_unset(t_data *data)
{
	if (data->cmd_lst->args[1] == NULL)
	{
		printf("unset : not enough arguments");
		g_exit_status = 1;
		return ;
	}
	while (data->cmd_lst->args[1])
	{
		ft_unset_arg(data);
		data->cmd_lst->args += 1;
	}
}

// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	ft_unset(argv[1], &envp);
// 	ft_env(envp);
// }
