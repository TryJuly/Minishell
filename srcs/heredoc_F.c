/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_F.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:54:55 by strieste          #+#    #+#             */
/*   Updated: 2026/01/23 12:50:50 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	handle_heredoc(char *delimiter, t_data *data);
static int	should_expand_heredoc(char *delimiter);
static int	run_heredoc(char *delimiter, t_data *data);
static void	loop_heredoc(int fd, int expand, char *delimiter, t_data *data);

int	heredoc_check(char **array, t_data *data)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (i > 0 && !ft_strncmp(array[i - 1], "<<", 3))
		{
			if (handle_heredoc(array[i], data) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

static int	handle_heredoc(char *delimiter, t_data *data)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
			return (ft_putstr_fd("Msh: Fork PID\n", 2), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		run_heredoc(delimiter, data);
		exit(0);
	}
	waitpid(pid, &status, 0);
	signal(SIGINT, sighandler);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		g_exit_status = 130;
		return (-1);
	}
	return (0);
}

static int	run_heredoc(char *delimiter, t_data *data)
{
	int		fd;
    int 	expand;
    char	*clean_delimiter;

	expand = should_expand_heredoc(delimiter);
	clean_delimiter = remove_quote(delimiter);
	fd = open("/tmp/heredoc", O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return (ft_putstr_fd("Msh: Error open fd\n", 2), -1);
    loop_heredoc(fd, expand, clean_delimiter, data);
	close(fd);
    free(clean_delimiter);
	return (0);
}

static void	loop_heredoc(int fd, int expand, char *delimiter, t_data *data)
{
	char	*line;
	
	while (1)
    {
        line = readline("heredoc> ");
        if (!line || ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
        {
            free(line);
            break;
        }
        if (expand)
            line = expand_token(line, data);
        write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
        free(line);
    }
	return ;
}

static int should_expand_heredoc(char *delimiter)
{
    int i = 0;
    while (delimiter[i])
    {
        if (delimiter[i] == '\'' || delimiter[i] == '\"')
            return (0); 
        i++;
    }
    return (1);
}

char	*remove_quote(char *str)
{
	int		i;
	int		j;
	char	*res;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	res = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!res)
		return (error_malloc(), NULL);
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && quote == 0)
			quote = str[i++];
		else if (str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

// int	handle_heredoc(char *delimiter, t_data *data)
// {
// 	int		fd;
//     int 	expand;
//     char	*clean_delimiter;

// 	expand = should_expand_heredoc(delimiter);
// 	clean_delimiter = remove_quotes(delimiter);
// 	fd = open("/tmp/heredoc", O_RDWR | O_TRUNC | O_CREAT, 0777);
// 	if (fd == -1)
// 		return (ft_putstr_fd("Msh: Error open fd\n", 2), -1);
//     while (1)
//     {
//         line = readline("heredoc> ");
//         if (!line || ft_strcmp(line, clean_delimiter) == 0)
//         {
//             free(line);
//             break;
//         }
//         if (expand)
//             line = expand_token(line, data);
//         write(fd, line, ft_strlen(line));
// 		write(fd, "\n", 1);
//         free(line);
//     }
// 	close(fd);
//     free(clean_delimiter);
// }