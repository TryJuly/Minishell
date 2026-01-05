/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_v1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:52:49 by cbezenco          #+#    #+#             */
/*   Updated: 2026/01/05 15:32:49 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*read_pipe(int *pipefd)
{
	char	*buf;
	int		numread;
	char	*res;
	int		total;

	numread = -1;
	res = "";
	total = 0;
	buf = malloc(101);
	if (!buf)
		return (ft_putstr_fd("Msh: Error Malloc\n", 2), NULL);
	while (numread != 0)
	{
		numread = read(pipefd[0], buf, 100);
		total += numread;
		if (numread == -1)
			return (perror("Msh: "), NULL);
		else if (numread == 0)
			break ;
		buf[total + 1] = 0;
		res = ft_strjoin(res, buf);
	}
	free(buf);
	return (res);
}

char	*exec_command(char **args, t_data *data)
{
	pid_t	child;
	int		pipefd[2];
	char	*res;

	if (pipe(pipefd) == -1)
		return (ft_putstr_fd("Msh: Init PIPE\n", 2), NULL);
	child = fork();
	if (child < 0)
		return (ft_putstr_fd("Msh: Fork PID\n", 2), NULL);
	if (child == 0)
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		execve(args[0], args, data->envp);
		error_child(args, data);
	}
	close(pipefd[1]);
	wait(&child);
	res = read_pipe(pipefd);
	if (!res)
		perror("Msh: ");
	return (res);
}

char	*expand_command_value(char *new_str, t_data *data)
{
	char	**args;
	char	*res;
	char	*tmp;

	if (!data)
		return (NULL);
	tmp = ft_strtrim(new_str, "$()");
	if (!tmp)
		return (NULL);
	free(new_str);
	new_str = expand_line(tmp, data);
	if (!new_str)
		return (NULL);
	free(tmp);
	args = ft_split(new_str, ' ');
	get_cmdpath(&data, data->envp);
	find_path_1(&args[0], data->path);
	res = exec_command(args, data);
	ft_free_array(&args);
	return (res);
}

char	*expand_var_value(char *new_str, t_data *data)
{
	int		i;
	char	*temp;
	char	*value;

	i = 0;
	temp = new_str;
	temp += 1;
	if (new_str[1] == ' ' || !new_str[1])
		return (ft_strdup(new_str));
	if (new_str[1] == '?')
		return (question_mark(temp));
	while (data->envp[i])
	{
		if (ft_strncmp(temp, data->envp[i], ft_strlen(temp) - 1) == 0)
		{
			value = ft_strchr(data->envp[i], '=');
			value += 1;
			temp = ft_strdup(value);
			return (temp);
		}
		i++;
	}
	value = ft_strdup("");
	return (value);
}
