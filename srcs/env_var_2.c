/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:52:49 by cbezenco          #+#    #+#             */
/*   Updated: 2026/01/23 12:34:01 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// static char	*read_pipe(int *pipefd);
static char	*question_mark(char *str);
// static char	*exec_command(char **args, t_data *data);

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

// static char	*read_pipe(int *pipefd)
// {
// 	char	*buf;
// 	int		numread;
// 	char	*res;
// 	char	*temp;

// 	numread = -1;
// 	res = ft_strdup("");
// 	buf = malloc(101);
// 	if (!buf)
// 		return (ft_putstr_fd("Msh: Error Malloc\n", 2), NULL);
// 	while (numread != 0)
// 	{
// 		numread = read(pipefd[0], buf, 100);
// 		if (numread == -1)
// 			perror("Msh: ");
// 		else if (numread == 0)
// 			break ;
// 		buf[numread] = 0;
// 		temp = ft_strdup(res);
// 		free(res);
// 		res = ft_strjoin(temp, buf);
// 		free(temp);
// 	}
// 	free(buf);
// 	return (res);
// }

// static char	*exec_command(char **args, t_data *data)
// {
// 	pid_t	child;
// 	int		pipefd[2];
// 	char	*res;

// 	pipe(pipefd);
// 	child = fork();
// 	if (child == 0)
// 	{
// 		dup2(pipefd[1], 1);
// 		close(pipefd[0]);
// 		if (execve(args[0], args, data->envp) == -1)
// 		{
// 			perror("Msh: ");
// 		}
// 	}
// 	close(pipefd[1]);
// 	wait(&child);
// 	res = read_pipe(pipefd);
// 	if (!res)
// 		perror("Msh: ");
// 	return (res);
// }

static char	*question_mark(char *str)
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

// char	*expand_command_value(char *new_str, t_data *data)
// {
// 	char	**args;
// 	char	*res;
// 	char	*temp;
// 	char	*str;

// 	if (!data)
// 		return (NULL);
// 	temp = ft_strtrim(new_str, "$()");
// 	str = expand_line(temp, data);
// 	args = ft_split(str, ' ');
// 	get_cmdpath(&data, data->envp);
// 	find_path_1(&args[0], data->path);
// 	res = exec_command(args, data);
// 	ft_free_array(&args);
// 	free(temp);
// 	free(str);
// 	return (res);
// }
