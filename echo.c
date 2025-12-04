/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:41:25 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/04 09:51:06 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_echo(char *str)
{
	printf("%s\n", str);
}

void	ft_echo_n(char *str)
{
	printf("%s", str);
}

// int	main(void)
// {
// 	char	*str = "Salut";

// 	ft_echo(str);
// 	ft_echo_n(str);
// }
