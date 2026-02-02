/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:56:47 by strieste          #+#    #+#             */
/*   Updated: 2026/01/23 17:16:40 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	exec_lst_cmd(t_data *data, t_cmd *cmd, pid_t *pid, int count);
static int	child(t_cmd *cmd, t_data *data, int prev_fd, int *pipe_fd);
static void	error_child(t_cmd *cmd, t_data *data);
static void	help_exec_lst(int *p_fd, int *p_in, int *p_out, t_cmd *cmd);

int	exec_cmd(t_data *data)
{
	pid_t	*pid;
	int		status;
	int		count;
	int		number_cmd;

	count = 0;
	number_cmd = lst_size(data->cmd_lst);
	if (number_cmd == 1 && !data->cmd_lst->redir)
		if (check_builtin(data, data->cmd_lst) == 1)
			return (0);
	pid = malloc(number_cmd * sizeof(pid_t));
	if (!pid)
		return (free_all(data), ft_putstr_fd("Msh: Error malloc pid\n", 2), 1);
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
	free(pid);
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
		init_pipe(pipe_fd);
		if (cmd->next)
			if (pipe(pipe_fd) == -1)
				return (ft_putstr_fd("Msh: Init PIPE\n", 2), 1);
		pid[count] = fork();
		if (pid[count] < 0)
			return (ft_putstr_fd("Msh: Fork PID\n", 2), 1);
		if (pid[count] == 0)
			child(cmd, data, prev_fd, pipe_fd);
		help_exec_lst(&prev_fd, &pipe_fd[1], &pipe_fd[0], cmd);
		count++;
		cmd = cmd->next;
	}
	return (0);
}

static void	help_exec_lst(int *p_fd, int *p_in, int *p_out, t_cmd *cmd)
{
	if (*p_fd != -1)
	{
		close(*p_fd);
		*p_fd = -1;
	}
	if (cmd->next)
	{
		close(*p_in);
		*p_fd = *p_out;
	}
	else
	{
		if (*p_in != -1)
			close(*p_in);
		if (*p_out != -1)
			close(*p_out);
	}
	return ;
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
	if (!search_occur(cmd->args[0], '/'))
		set_path(data, &(cmd));
	close_dup_fd(&in, &out, pipe_fd, &prev_fd);
	if (check_builtin(data, cmd) == 1)
		return (exit(0), 0);
	execve(cmd->args[0], cmd->args, data->envp);
	error_child(cmd, data);
	return (0);
}

static void	error_child(t_cmd *cmd, t_data *data)
{
	if (ft_strchr(cmd->args[0], '/'))
	{
		ft_putstr_fd("Msh: ", 2);
		perror(cmd->args[0]);
		free_all(data);
		if (errno == EACCES)
			exit(126);
		exit(127);
	}
	ft_putstr_fd("Msh: Command not found: ", 2);
	ft_putendl_fd(cmd->args[0], 2);
	free_all(data);
	exit(127);
}
