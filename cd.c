/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:51:33 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/04 11:05:56 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_cd(char *path)
{
	if (access(path, F_OK) == -1)
	{
		printf("No such file or directory: ");
		perror(path);
		return ;
	}
	if (chdir(path) == -1)
		printf("oups");
}

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	ft_cd(argv[1]);
// 	printf("%s\n", getcwd(argv[1], 100));
// }
