/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:21:05 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/04 15:34:33 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	ft_unset(char *str, char ***envp)
{
	int		i;
	int		envp_size;
	char	**new_envp;

	i = 0;
	envp_size = arr_size(*envp);
	new_envp = malloc((sizeof(char *) * (envp_size - 1)));
	if (!new_envp)
		printf("pas bon");
	while (envp[0][i])
	{
		if (ft_strncmp(envp[0][i], str, ft_strlen(str)) == 0)
		{
			**envp++;
			continue ;
		}
		new_envp[i] = envp[0][i];
		i++;
	}
	new_envp[i] = NULL;
	*envp = new_envp;
}
