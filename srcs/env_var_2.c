/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:52:49 by cbezenco          #+#    #+#             */
/*   Updated: 2026/01/05 10:20:26 by cbezenco         ###   ########.fr       */
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
	get_cmdpath(&data, data->envp);
	find_path_1(&args[0], data->path);
	res = exec_command(args, data);
	return (res);
}

char	*question_mark(char *str)
{
	char	*temp;
	char	*stat_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	stat_str = ft_itoa(g_exit_status);
	if (str[i] == '?' && !str[i + 1])
		return (stat_str);
	else
	{
		temp = malloc(ft_strlen(str) + ft_strlen(stat_str));
		while (str[i])
		{
			if (str[i] == '?')
			{
				while (stat_str[j])
				{
					temp[j] = stat_str[j];
					j++;
				}
			}
			else
				temp[j++] = str[i];
			i++;
		}
		temp[j] = 0;
	}
	return (temp);
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
		return (new_str);
	if (new_str[1] == '?')
		return (question_mark(temp));
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
