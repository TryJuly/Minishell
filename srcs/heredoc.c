/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 11:02:01 by cbezenco          #+#    #+#             */
/*   Updated: 2025/12/31 11:24:31 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*expand_line(char *line, t_data *data);

// void	exec_heredoc_cmd(int here_fd, t_cmd *here_cmd, t_data *data)
// {
// 	pid_t	child;
// 	int		pipefd[2];
// 	//char	*buf;
// 	//int		numread;
// 	//char	*res;
// 	//int		total;

// 	pipe(pipefd);
// 	child = fork();
// 	if (child == 0)
// 	{
// 		dup2(here_fd, 0);
// 		close(here_fd);
// 		//dup2(pipefd[1], 1); // RECHECK CETTE MERDE LAAAAAAAAA ^^
// 		//close(pipefd[0]);
// 		//here_cmd->args = ft_split(here_cmd->args[0], ' ');
// 		here_cmd->args[0] = find_path(here_cmd->args[0], data->path);
// 		if (execve(here_cmd->args[0], here_cmd->args, data->envp) == -1)
// 			printf("fin de carriere\n");
// 	}
// 	close(pipefd[1]);
// 	wait(&child);
// 	// numread = -1;
// 	// res = "";
// 	// total = 0;
// 	// buf = malloc(101);
// 	// while (numread != 0)
// 	// {
// 	// 	numread = read(pipefd[0], buf, 100);
// 	// 	printf("%i\n", numread);
// 	// 	total += numread;
// 	// 	if (numread == -1)
// 	// 		printf("la poisse\n");
// 	// 	else if (numread == 0)
// 	// 		break ;
// 	// 	buf[total + 1] = 0;
// 	// 	res = ft_strjoin(res, buf);
// 	// }
// 	// free(buf);
// 	// printf("%s\n", res);
// }

char	*delimiter_in_input(char *input)
{
	int		i;
	int		j;
	char	*del;

	i = 0;
	while (input[i] == ' ')
		i++;
	j = i;
	while (ft_isascii(input[j]) && input[j] != ' ' && input[j] != '<')
		j++;
	del = ft_substr(input, i, j);
	input += j + i;
	return (del);
}

void	heredoc(char *input, t_data *data)
{
	char	*delimiter;
	char	*line;
	char	*res;
	int		fd;

	fd = open("/tmp/heredoc", O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		printf("oups");
	delimiter = delimiter_in_input(input);
	printf("%s : %s\n", delimiter, input);
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
		{
			free(line);
			close(fd);
			break ;
		}
		res = expand_line(line, data);
		write(fd, res, ft_strlen(res));
		write(fd, "\n", 1);
		free(line);
		free(res);
	}
}

char	*expand_line(char *line, t_data *data)
{
	char	**exp_vars;
	int		dollars;
	int		i;
	char	*res;

	i = 0;
	dollars = count_dollars(line);
	if (dollars == 0)
		return (ft_strdup(line));
	exp_vars = ft_split_dollars(line, dollars);
	while (exp_vars[i])
	{
		if (exp_vars[i][0] == '$' && exp_vars[i][1] == '(')
			exp_vars[i] = expand_command_value(exp_vars[i], data);
		else if (exp_vars[i][0] == '$')
			exp_vars[i] = expand_var_value(exp_vars[i], data);
		i++;
	}
	res = ft_unsplit(exp_vars);
	return (res);
}

// char	*delimiter_in_input(char *input)
// {
// 	int	i;
// 	int j;
// 	char	*del;

// 	i = 0;
// 	// while (input[i])
// 	// {
// 	// 	if (input[i] == '<')
// 	// 	{
// 	// 		while (input[i] == '<' || input[i] == ' ')
// 	// 			i++;
// 	// 		j = i;
// 	// 		break ;
// 	// 	}
// 	// 	i++;
// 	// }
// 	while (input[i] == ' ')
// 		i++;
// 	j = i;
// 	while (ft_isascii(input[j]) && input[j] != ' ' && input[j] != '<')
// 		j++;
// 	del = ft_substr(input, i, j);
// 	input += j + i;
// 	return (del);
// }