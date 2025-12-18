/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:34:29 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/18 11:46:16 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	append_mode(t_data *data, t_cmd *cmd)
{
	int	fd;

	if (access(cmd->redir->file, F_OK) == -1)
		fd = open(cmd->redir->file, O_CREAT, 0777);
	else
	{
		if (access(cmd->redir->file, R_OK, W_OK) == -1)
			perror("problemo fratello\n");
		fd = open(cmd->redir->file, O_APPEND);
	}
	cmd->redir->
	// return fd ??
}
