/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 11:02:01 by cbezenco          #+#    #+#             */
/*   Updated: 2026/01/05 12:30:07 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*expand_line(char *line, t_data *data);

char	*delimiter_in_input(char *str)
{
	int		i;
	int		j;
	char	*del;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	j = i;
	while (str[j] && ft_isascii(str[j]) && str[j] != ' ' && str[j] != '<')
		j++;
	del = ft_substr(str, i, j);
	str += j + i;
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
	free(delimiter);
}

char	**other_ft_split_dollars(char *str, int dollars)
{
	int		i;
	int		j;
	int		res_i;
	char	**res;
	char	*temp;

	i = 0;
	res_i = 0;
	res = malloc(sizeof(char *) * (dollars + 3));
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = i + 1;
			while (str[j] != '$' && str[j] != ' ' && str[j] != '\'' && str[j] != '"' && str[j])
				j++;
			temp = ft_substr(str, i, j - i);
			res[res_i++] = temp;
			i = j - 1;
		}
		else
		{
			j = i + 1;
			while (str[j] != '$' && str[j])
				j++;
			temp = ft_substr(str, i, j - i);
			res[res_i++] = temp;
			i = j - 1;
		}
		i++;
	}
	res[res_i] = NULL;
	return (res);
}

char	*expand_line(char *line, t_data *data)
{
	char	**exp_vars;
	int		dollars;
	int		i;
	char	*res;

	i = 0;
	dollars = count_dollars(line);
	if (!no_dollars(line))
		return (ft_strdup(line));
	exp_vars = other_ft_split_dollars(line, dollars);
	while (exp_vars[i])
	{
		if (exp_vars[i][0] == '$' && exp_vars[i][1] == '(')
			exp_vars[i] = expand_command_value(exp_vars[i], data);
		else if (exp_vars[i][0] == '$')
			exp_vars[i] = expand_var_value(exp_vars[i], data);
		i++;
	}
	res = ft_unsplit(exp_vars);
	ft_free_array(&exp_vars);
	return (res);
}
