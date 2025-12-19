/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:56:47 by strieste          #+#    #+#             */
/*   Updated: 2025/12/19 09:52:42 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	exec_lst_cmd(t_data *data, t_cmd *cmd, pid_t *pid, int count);
static int	child(t_cmd *cmd, t_data *data, int prev_fd, int *pipe_fd);
static void	error_child(t_cmd *cmd);
static void	is_valide_cmd(t_data *data, t_cmd **cmd);

int exec_cmd(t_data *data)
{
	pid_t *pid;
	int status;
	int count;
	int number_cmd;

	count = 0;
	number_cmd = lst_size(data->cmd_lst);
	// pid = calloc(number_cmd, sizeof(pid_t)); // If use ft_calloc minishell in minishell fail
	pid = malloc(number_cmd * sizeof(pid));
	if (!pid)
		return (printf("Error malloc pid\n"), 1);
	exec_lst_cmd(data, data->cmd_lst, pid, count);
	while (count < number_cmd)
	{
		waitpid(pid[count], &status, 0); // change Value $? with status
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
			// La valeur renvoyée par une commande simple est son état final ou 128+n si la commande a été terminée par le signal n
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
				return (printf("%sError init PIPE\n%s", RED, NC), 1); // Error Pipe init exit--code
		pid[count] = fork();										  // If BUILTIN command and no pipe execute in parent process no fork
		if (pid[count] < 0)
			return (printf("Error fork\n"), 1);
		if (pid[count] == 0)
			child(cmd, data, prev_fd, pipe_fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
			close(pipe_fd[1]);
		prev_fd = cmd->next ? pipe_fd[0] : -1;
		count++;
		cmd = cmd->next;
	}
	return (1);
}

static int child(t_cmd *cmd, t_data *data, int prev_fd, int *pipe_fd)
{
	int in;
	int out;

	in = STDIN_FILENO;
	out = STDOUT_FILENO;
	if (prev_fd != -1)
		in = prev_fd;
	if (cmd->next)
		out = pipe_fd[1];
	if (cmd->redir)
		redir_file(&(in), &(out), cmd->redir);
	close_dup_fd(&(in), &(out), pipe_fd, &(prev_fd));
	is_valide_cmd(data, &(cmd));
	execve(cmd->args[0], cmd->args, data->envp);
	error_child(cmd);
	return (0);
}

static void error_child(t_cmd *cmd)
{
	if (errno == ENOENT) // File or directory does not exist
	{
		printf("%szsh: command not found: %s%s\n", RED, cmd->args[0], NC);
		exit(127);
	}
	else if (errno == EACCES) // Permission denied
	{
		printf("%spermission denied%s\n", RED, NC);
		exit(126);
	}
	else
	{
		perror("minishell");
		exit(1);
	}
	return;
}

static void is_valide_cmd(t_data *data, t_cmd **cmd)
{
	struct stat st;

	if ((*cmd)->args[0][0] != '/')
	{
		if (find_path_1((*cmd)->args, data->path))
		{
			printf("%scommand not foundLLL%s\n", RED, NC);
			exit(127);
		}
	}
	if (stat((*cmd)->args[0], &st) == 0 && S_ISDIR(st.st_mode))
	{
		perror("is a directoy");
		exit(126);
	}
	return;
}

//			##########		SAVE	##########

// int	exec_cmd(t_data *data)
// {
// 	t_cmd	*tmp;
// 	pid_t	*pid;
// 	int		pipe_fd[2];
// 	int		status;
// 	int		prev_fd;
// 	int		count;
// 	int		number_cmd;

// 	tmp = data->cmd_lst;
// 	prev_fd = -1;
// 	count = 0;
// 	number_cmd = lst_size(data->cmd_lst);
// 	pid = calloc(number_cmd, sizeof(pid_t));
// 	if (!pid)
// 		return (printf("Error malloc pid\n"), 1);
// 	while (tmp)
// 	{
// 		ft_bzero(pipe_fd, 2);
// 		if (tmp->next)
// 			if (pipe(pipe_fd) == -1)
// 				return (printf("%sError init PIPE\n%s", RED, NC), 1);	// Error Pipe init exit--code
// 		pid[count] = fork();	// If BUILTIN command and no pipe execute in parent process no fork
// 		if (pid[count] < 0)
// 			return (printf("Error fork\n"), 1);
// 		if (pid[count] == 0)
// 			child_process(tmp, data, prev_fd, pipe_fd);
// 		if (prev_fd != -1)
// 			close(prev_fd);
// 		if (tmp->next)
// 			close(pipe_fd[1]);
// 		prev_fd = tmp->next ? pipe_fd[0] : -1;
// 		count++;
// 		tmp = tmp->next;
// 	}
// 	number_cmd= 0;
// 	while (number_cmd < count)
// 		waitpid(pid[number_cmd++], &status, 0);	// change Value $? with status
// 	return (0);
// }

// static int	child_process(t_cmd *cmd, t_data *data, int prev_fd, int pipe_fd[2])
// {
// 	t_redir		*tmp;
// 	struct stat	st;
// 	int			in;
// 	int			out;

// 	in = STDIN_FILENO;
// 	out = STDOUT_FILENO;
// 	if (prev_fd != -1)
// 		in = prev_fd;
// 	if (cmd->next)
// 		out = pipe_fd[1];
// 	/*					APPLY ALL REDIR IF NEEDED				*/
// 	if (cmd->redir)
// 	{
// 		tmp = cmd->redir;
// 		while (tmp)
// 		{
// 			if (tmp->type == R_IN)
// 			{
// 				if (in != STDIN_FILENO)
// 					in = close(in);
// 				if (access(tmp->file, F_OK))
// 					return (perror("minishell"), 1);
// 				if (access(tmp->file, R_OK))
// 					return (perror("minishell"), 1);
// 				in = open(tmp->file, O_RDONLY);
// 				if (in < 0)
// 					return (perror("minishell"), 1);		// Error Exit code
// 			}
// 			else if (tmp->type == R_OUT)
// 			{
// 				if (out != STDOUT_FILENO)
// 					out = close(out);		// check return close
// 				out = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 				if (out < 0)
// 					return (printf("Error create: %s\n", tmp->file), 1);	// Error Exit code
// 			}
// 			else if (tmp->type == R_APPEND)
// 			{
// 				if (out != STDOUT_FILENO)
// 					out = close(out);		// check return close
// 				out = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 				if (out < 0)
// 					return (printf("Error create or open:%s\n", tmp->file), 1);	// Errror Exit code
// 			}
// 			tmp = tmp->next;
// 		}
// 	}
// 		/*				CLOSE ALL FD BEFORE CHECK COMMAND			*/
// 	if (in != STDIN_FILENO)
// 	{
// 		dup2(in, STDIN_FILENO);
// 		if (in == prev_fd)
// 			prev_fd = -1;
// 		close(in);
// 	}
// 	if (out != STDOUT_FILENO)
// 	{
// 		dup2(out, STDOUT_FILENO);
// 		if (out == pipe_fd[1])
// 			pipe_fd[1] = -1;
// 		close(out);
// 	}
// 	if (prev_fd != -1)
// 		close(prev_fd);
// 	if (pipe_fd[1] != -1)
// 		close(pipe_fd[1]);
// 	if (pipe_fd[0])
// 		close(pipe_fd[0]);		// Need condition for close
// 	//				Find command in path and if is valide
// 	/*				CHECK IF IS VALID COMMAND OR BUILTIN IF PIPE	*/
// 	if (cmd->args[0][0] != '/')
// 		if (find_path(&cmd->args[0], data->path))
// 		{
// 			printf("%scommand not foundLLL%s\n", RED, NC);
// 			exit(127);
// 		}
// 	/*			Check if is a directory								*/
// 	if (stat(cmd->args[0], &st) == 0 && S_ISDIR(st.st_mode))
// 	{
// 		perror("is a directoy");
// 		exit(126);
// 	}
// 	execve(cmd->args[0], cmd->args, data->envp);
// 	/*			If execve fail return Error with errno				*/
// 	if (errno == ENOENT)	// File or directory does not exist
// 	{
// 		printf("%szsh: command not found: %s%s\n", RED, cmd->args[0], NC);
// 		exit(127);
// 	}
// 	else if (errno == EACCES)	// Permission denied
// 	{
// 		printf("%spermission denied%s\n", RED, NC);
// 		exit(126);
// 	}
// 	else
// 	{
// 		perror("minishell");
// 		exit(1);
// 	}
// 	return (0);
// }