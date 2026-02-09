/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:16:43 by cbezenco          #+#    #+#             */
/*   Updated: 2025/10/07 14:48:44 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	div_10(long n)
{
	int	c;

	c = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		c++;
	}
	return (c);
}

static void	help(char *str, int n, int *i)
{
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		str[*i] = '-';
		*i += 1;
		nbr = -nbr;
	}
	if (nbr > 9)
	{
		help(str, (nbr / 10), i);
		help(str, (nbr % 10), i);
	}
	else if (nbr <= 9)
	{
		str[*i] = nbr + '0';
		*i += 1;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	i = 0;
	if (n < 0)
		str = malloc(sizeof(char) * (div_10(n) + 2));
	else
		str = malloc(sizeof(char) * (div_10(n) + 1));
	if (!str)
		return (NULL);
	help(str, n, &i);
	str[i] = '\0';
	return (str);
}
