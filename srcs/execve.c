/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:56:47 by strieste          #+#    #+#             */
/*   Updated: 2025/12/15 10:07:23 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	exec_cmd(t_data *data)
{
	t_cmd	*tmp;
	pid_t	child;
	int		pipe_fd[2];
	
	tmp = data->cmd_lst;
	while (tmp)
	{
		if (tmp->next)
			if (pipe(pipe_fd) == -1)
				return (printf("%sError init PIPE\n%s", RED, NC), 1);	// Error Pipe init exit--code
	}
}

// void	pipex(t_data *data)
// {
// 	int		pipe_fd[2];
// 	pid_t	child1;
// 	pid_t	child2;
// 	// int		status;

// 	if (pipe(pipe_fd) == -1)
// 		exit(1); // Error function check
// 	child1 = fork();
// 	if (child1 < 0)
// 		return ;	// Error FORK SEE
// 	if (child1 == 0)
// 	{
// 		close(pipe_fd[0]);
// 		close(data->fd_out);
// 		child(data->fd_in, pipe_fd[1], data->cmd_1, data);
// 	}
// 	close(pipe_fd[1]);
// 	child2 = fork();
// 	if (child2 < 0)
// 		return ;	// Error FORK SEE
// 	if (child2 == 0)
// 	{
// 		close(pipe_fd[1]);
// 		close(data->fd_in);
// 		child(pipe_fd[0], data->fd_out, data->cmd_2, data);
// 	}
// 	close(pipe_fd[0]);
// 	waitpid(child1, NULL, 0);
// 	waitpid(child2, NULL, 0);
// 	return ;
// }

// void	child(int fd_in, int fd_out, char **cmd, t_data *data)
// {
// 	dup2(fd_in, STDIN_FILENO);
// 	dup2(fd_out, STDOUT_FILENO);
// 	close(fd_in);
// 	close(fd_out);
// 	execve(cmd[0], cmd, data->envp);
// 	// perror("execve");
// 	ft_clean_struct(data);
// 	close(data->fd_in);
// 	close(data->fd_out);
// 	exit(1); // Need To FREE
// }
