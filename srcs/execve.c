/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:56:47 by strieste          #+#    #+#             */
/*   Updated: 2025/12/22 13:30:47 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	exec_lst_cmd(t_data *data, t_cmd *cmd, pid_t *pid, int count);
static int	child(t_cmd *cmd, t_data *data, int prev_fd, int *pipe_fd);
static void	error_child(t_cmd *cmd);
static void	is_valide_cmd(t_data *data, t_cmd **cmd);

int	exec_cmd(t_data *data)
{
	pid_t	*pid;
	int		status;
	int		count;
	int		number_cmd;

	count = 0;
	number_cmd = lst_size(data->cmd_lst);
	if (number_cmd == 1)
		if (check_builtin(data, data->cmd_lst) == 1)
			return (0);
	pid = malloc(number_cmd * sizeof(pid));
	if (!pid)
		return (printf("Error malloc pid\n"), 1);
	exec_lst_cmd(data, data->cmd_lst, pid, count);
	while (count < number_cmd)
	{
		waitpid(pid[count], &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
		count++;
	}
	return (0);
}

static int	exec_lst_cmd(t_data *data, t_cmd *cmd, pid_t *pid, int count)
{
	int		pipe_fd[2];
	int		prev_fd;

	prev_fd = -1;
	count = 0;
	while (cmd)
	{
		ft_bzero(pipe_fd, 2);
		if (cmd->next)
			if (pipe(pipe_fd) == -1)
				return (printf("%sError init PIPE\n%s", RED, NC), 1);
		pid[count] = fork();
		if (pid[count] < 0)
			return (printf("Error fork\n"), 1);
		if (pid[count] == 0)
			child(cmd, data, prev_fd, pipe_fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
			close(pipe_fd[1]);
		if (cmd->next)
			prev_fd = pipe_fd[0];
		else
			prev_fd = -1;
		count++;
		cmd = cmd->next;
	}
	return (1);
}

static int	child(t_cmd *cmd, t_data *data, int prev_fd, int *pipe_fd)
{
	int	in;
	int	out;

	in = STDIN_FILENO;
	out = STDOUT_FILENO;
	if (prev_fd != -1)
		in = prev_fd;
	if (cmd->next)
		out = pipe_fd[1];
	if (cmd->redir)
		redir_file(&(in), &(out), cmd->redir);
	close_dup_fd(&(in), &(out), pipe_fd, &(prev_fd));
	if (check_builtin(data, cmd) == 1)
		return (exit(0), 0);
	is_valide_cmd(data, &(cmd));
	execve(cmd->args[0], cmd->args, data->envp);
	error_child(cmd);
	return (0);
}

static void	error_child(t_cmd *cmd)
{
	if (errno == ENOENT)
	{
		printf("%sMsh: command not found: %s%s\n", RED, cmd->args[0], NC);
		exit(127);
	}
	else if (errno == EACCES)
	{
		printf("%sMsh: permission denied%s\n", RED, NC);
		exit(126);
	}
	else
	{
		perror("Msh");
		exit(1);
	}
	return ;
}

static void	is_valide_cmd(t_data *data, t_cmd **cmd)
{
	struct stat	st;

	if ((*cmd)->args[0][0] != '/')
	{
		if (find_path_1((*cmd)->args, data->path))
		{
			printf("%sMsh: command not foundLLL%s\n", RED, NC);
			exit(127);
		}
	}
	if (stat((*cmd)->args[0], &st) == 0 && S_ISDIR(st.st_mode))
	{
		perror("is a directoy");
		exit(126);
	}
	return ;
}
