/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 10:36:01 by strieste          #+#    #+#             */
/*   Updated: 2025/12/18 15:02:08 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	redir_in(int *in, t_redir *redir);
static int	redir_out(int *out, t_redir *redir);
static int	redir_out_append(int *out, t_redir *redir);
static int	redir_out_heredoc(int *in, t_redir *redir);

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
			if (redir_out_heredoc(in, redir))
				return (exit(126), 1);
		}
		redir = redir->next;
	}
	return (0);
}

int	close_dup_fd(int *in, int *out, int *pipe_fd, int *prev_fd)
{
	if (*in != STDIN_FILENO)
	{
		dup2(*in, STDIN_FILENO);
		if (*in == *prev_fd)
			*prev_fd = -1;
		close(*in);
	}
	if (*out != STDOUT_FILENO)
	{
		dup2(*out, STDOUT_FILENO);
		if (*out == pipe_fd[1])
			pipe_fd[1] = -1;
		close(*out);
	}
	if (*prev_fd != -1)
		close(*prev_fd);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	if (pipe_fd[0])
		close(pipe_fd[0]);
	return (0);
}

static int	redir_out_heredoc(int *in, t_redir *redir)
{
	int	status;
	
	status = 0;
	if (*in != STDOUT_FILENO)
		status = close(*in);
	if (status == -1)
		return (perror("Minishell"), -1);
	*in = open(redir->file, O_RDONLY);
	if (*in < 0)
		return (perror("Minishell"), -1);
	return (0);
}

static int	redir_out_append(int *out, t_redir *redir)
{
	int	status;

	status = 0;
	if (*out != STDOUT_FILENO)
		status = close(*out);
	if (status == -1)
		return (perror("Minishell"), -1);
	*out = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*out < 0)
		return (perror("Minishell"), -1);
	return (0);
}

static int	redir_out(int *out, t_redir *redir)
{
	int	status;
	
	status = 0;
	if (*out != STDERR_FILENO)
		close(*out);
	if (status == -1)
		return (perror("Minishell"), -1);
	*out = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*out < 0)
		return (perror("Minishell"), -1);
	return (0);
}

static int	redir_in(int *in, t_redir *redir)
{
	int	status;
	
	status = 0;
	if (*in == STDIN_FILENO)
		close(*in);
	if (status == -1)
		return (perror("Minishell"), -1);
	if (access(redir->file, F_OK))
		return (perror("Minishell"), -1);
	if (access(redir->file, R_OK))
		return (perror("Minishell"), -1);
	*in = open(redir->file, O_RDONLY);
	if (*in < 0)
		return (perror("Minishell"), -1);
	return (0);
}
