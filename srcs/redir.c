/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 10:36:01 by strieste          #+#    #+#             */
/*   Updated: 2025/12/22 13:03:22 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	redir_in(int *in, t_redir *redir);
static int	redir_out(int *out, t_redir *redir);
static int	redir_out_append(int *out, t_redir *redir);
static int	redir_out_heredoc(int *in);

int	redir_file(int *in, int *out, t_redir *redir)
{
	while (redir)
	{
		if (redir->type == R_IN)
		{
			if (redir_in(in, redir))
				return (exit(126), 1);
		}
		else if (redir->type == R_OUT)
		{
			if (redir_out(out, redir))
				return (exit(126), 1);
		}
		else if (redir->type == R_APPEND)
		{
			if (redir_out_append(out, redir))
				return (exit(126), 1);
		}
		else if (redir->type == R_HEREDOC)
		{
			if (redir_out_heredoc(in))
				return (exit(126), 1);
		}
		redir = redir->next;
	}
	return (0);
}

static int	redir_out_heredoc(int *in)
{
	int	status;

	status = 0;
	if (*in != STDOUT_FILENO)
		status = close(*in);
	if (status == -1)
		return (perror("Msh"), -1);
	*in = open("/tmp/heredoc", O_RDONLY);
	if (*in < 0)
		return (perror("Msh"), -1);
	return (0);
}

static int	redir_out_append(int *out, t_redir *redir)
{
	int	status;

	status = 0;
	if (*out != STDOUT_FILENO)
		status = close(*out);
	if (status == -1)
		return (perror("Msh"), -1);
	*out = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*out < 0)
		return (perror("Msh"), -1);
	return (0);
}

static int	redir_out(int *out, t_redir *redir)
{
	int	status;

	status = 0;
	if (*out != STDERR_FILENO)
		close(*out);
	if (status == -1)
		return (perror("Msh"), -1);
	*out = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*out < 0)
		return (perror("Msh"), -1);
	return (0);
}

static int	redir_in(int *in, t_redir *redir)
{
	int	status;

	status = 0;
	if (*in == STDIN_FILENO)
		close(*in);
	if (status == -1)
		return (perror("Msh"), -1);
	if (access(redir->file, F_OK))
		return (perror("Msh"), -1);
	if (access(redir->file, R_OK))
		return (perror("Msh"), -1);
	*in = open(redir->file, O_RDONLY);
	if (*in < 0)
		return (perror("Msh"), -1);
	return (0);
}
