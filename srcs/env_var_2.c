/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:52:49 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/22 13:53:55 by cbezenco         ###   ########.fr       */
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
		return (NULL);
	while (numread != 0)
	{
		numread = read(pipefd[0], buf, 100);
		total += numread;
		if (numread == -1)
			perror("Msh: ");
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

	pipe(pipefd);
	child = fork();
	if (child == 0)
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		if (execve(args[0], args, data->envp) == -1)
		{
			perror("Msh: ");
		}
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

	if (!data)
		return (NULL);
	new_str = ft_strtrim(new_str, "$()");
	new_str = expand_line(new_str, data);
	args = ft_split(new_str, ' ');
	find_path_1(&args[0], data->path);
	printf("%s : %s\n", args[0], args[1]);
	res = exec_command(args, data);
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
	if (new_str[1] == '?')
	{
		value = ft_itoa(g_exit_status);
		return (value);
	}
	while (data->envp[i])
	{
		if (ft_strncmp(temp, data->envp[i], ft_strlen(temp) - 1) == 0)
		{
			value = ft_strchr(data->envp[i], '=');
			value += 1;
			return (value);
		}
		i++;
	}
	value = "";
	return (value);
}
