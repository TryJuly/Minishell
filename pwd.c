/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:22:29 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/04 11:22:08 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
/* meme chose que getenv() haha*/
// char	*get_pwd(char **envp)
// {
// 	char	*temp;
// 	int		i;

// 	i = 0;
// 	temp = NULL;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
// 		{
// 			temp = envp[i];
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (!temp)
// 	{
// 		perror("pwd");
// 		exit(1);
// 	}
// 	temp = ft_strchr(temp, '/');
// 	return (temp);
// }

void	ft_pwd(void)
{
	char	*buf;
	size_t	size;

	buf = getenv("PWD");
	size = ft_strlen(buf) + 1;
	buf = getcwd(buf, size);
	printf("%s\n", buf);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	ft_pwd();
}
