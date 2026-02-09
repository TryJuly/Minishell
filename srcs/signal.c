/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:48:16 by strieste          #+#    #+#             */
/*   Updated: 2026/02/03 14:32:14 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	sighandler_v4(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	exit_status(131, 1);
}

void	sighandler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit_status(130, 1);
}

void	sigfin(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	exit_status(130, 1);
}

void	sigheredoc(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	exit(130);
}

int	exit_status(int status, int booly)
{
	static int	curr_status;

	if (booly)
		curr_status = status;
	else
		return (curr_status);
	return (0);
}
