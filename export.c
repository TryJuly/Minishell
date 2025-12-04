/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:06:07 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/04 15:20:53 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_env(char **envp);

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	ft_export(char *str, char ***envp)
{
	int		envp_size;
	char	**new_envp;
	int		i;

	i = 0;
	envp_size = arr_size(*envp);
	new_envp = malloc(sizeof(char *) * (envp_size + 1));
	if (!new_envp)
		printf("pas bon");
	while (envp[0][i])
	{
		new_envp[i] = ft_strdup(envp[0][i]);
		i++;
	}
	new_envp[i] = str;
	new_envp[i + 1] = NULL;
	*envp = new_envp;
}

// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	ft_export(argv[1], &envp);
// 	ft_export(argv[2], &envp);
// 	ft_env(envp);
// 	free(envp); // <---- attention mon grand !
// 	return (0);
// }
