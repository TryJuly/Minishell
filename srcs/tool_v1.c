/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_v1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:17:34 by strieste          #+#    #+#             */
/*   Updated: 2026/01/23 13:02:32 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	help_close_fd(int *prev_fd, int pipe_fd[2]);

int	close_dup_fd(int *in, int *out, int pipe_fd[2], int *prev_fd)
{
	if (*in != STDIN_FILENO)
	{
		dup2(*in, STDIN_FILENO);
		if (*in == *prev_fd)
			*prev_fd = -1;
		close(*in);
		*in = -1;
	}
	if (*out != STDOUT_FILENO)
	{
		dup2(*out, STDOUT_FILENO);
		if (*out == pipe_fd[1])
			pipe_fd[1] = -1;
		close(*out);
		*out = -1;
	}
	help_close_fd(prev_fd, pipe_fd);
	return (0);
}

static void	help_close_fd(int *prev_fd, int pipe_fd[2])
{
	if (*prev_fd > 0)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (pipe_fd[1] > 0)
	{
		close(pipe_fd[1]);
		pipe_fd[1] = -1;
	}
	if (pipe_fd[0] > 0)
	{
		close(pipe_fd[0]);
		pipe_fd[0] = -1;
	}
	return ;
}

void	set_path(t_data *data, t_cmd **cmd)
{
	struct stat	st;

	if (!(*cmd)->args[0] || (*cmd)->args[0][0] == '\0')
    {
        ft_putstr_fd("Msh: '': command not found\n", 2);
        exit(127);
    }
	if (data->path)
		ft_free_array(&data->path);
	get_cmdpath(&data, data->envp);
	find_path((*cmd)->args, data->path);
	if (stat((*cmd)->args[0], &st) == 0 && S_ISDIR(st.st_mode))
    {
        ft_putstr_fd("Msh: ", 2);
        ft_putstr_fd((*cmd)->args[0], 2);
        ft_putendl_fd(": is a directory", 2);
        exit(126);
    }
	return ;
}

void	init_pipe(int *pipe)
{
	pipe[0] = -1;
	pipe[1] = -1;
	return ;
}

// int	close_dup_fd(int *in, int *out, int pipe_fd[2], int *prev_fd)
// {
// 	if (*in > 0)
// 	{
// 		dup2(*in, STDIN_FILENO);
// 		if (*in == *prev_fd)
// 			*prev_fd = -1;
// 		close(*in);
// 		*in = -1;
// 	}
// 	if (*out > 1)
// 	{
// 		dup2(*out, STDOUT_FILENO);
// 		if (*out == pipe_fd[1])
// 			pipe_fd[1] = -1;
// 		close(*out);
// 		*out = -1;
// 	}
// 	if (*prev_fd > 0)
// 	{
// 		close(*prev_fd);
// 		*prev_fd = -1;
// 	}
// 	if (pipe_fd[1] > 0)
// 	{
// 		close(pipe_fd[1]);
// 		pipe_fd[1] = -1;
// 	}
// 	if (pipe_fd[0] > 0)
// 	{
// 		close(pipe_fd[0]);
// 		pipe_fd[0] = -1;
// 	}
// 	return (0);
// }