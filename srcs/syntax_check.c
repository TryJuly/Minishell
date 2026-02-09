/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbezenco <cbezenco@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:12:13 by strieste          #+#    #+#             */
/*   Updated: 2026/02/03 14:26:19 by cbezenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	error_print(int error);
static int	is_operator(char *token);

int	quote_check_input(char *str)
{
	size_t	count;
	char	quote;

	count = 0;
	quote = 0;
	while (str[count])
	{
		if (str[count] == '"' || str[count] == '\'')
		{
			quote = str[count++];
			while (str[count] && str[count] != quote)
				count++;
			if (str[count] != quote)
			{
				exit_status(2, 1);
				ft_putstr_fd("Msh: Unclosed quote\n", 2);
				return (1);
			}
		}
		count++;
	}
	return (0);
}

int	syntax_check(char **token)
{
	int	i;

	i = 0;
	if (!token || !token[0])
		return (0);
	if (ft_strncmp(token[0], "|", 2) == 0)
		return (error_print(1), 2);
	while (token[i])
	{
		if (is_redir(token[i]))
		{
			if (!token[i + 1] || is_operator(token[i + 1]))
				return (error_print(2), 2);
		}
		if (ft_strncmp(token[i], "|", 2) == 0)
		{
			if (!token[i + 1] || ft_strncmp(token[i + 1], "|", 2) == 0)
				return (error_print(3), 2);
		}
		i++;
	}
	return (0);
}

static int	is_operator(char *token)
{
	if (ft_strncmp(token, "|", 2) == 0)
		return (1);
	if (ft_strncmp(token, "<<", 3) == 0)
		return (1);
	if (ft_strncmp(token, ">>", 3) == 0)
		return (1);
	if (ft_strncmp(token, "<", 2) == 0)
		return (1);
	if (ft_strncmp(token, ">", 2) == 0)
		return (1);
	if (ft_strncmp(token, "<<", 3) == 0)
		return (1);
	return (0);
}

static void	error_print(int error)
{
	if (error == 1)
	{
		ft_putstr_fd("Msh: syntax error near unexpected token '|'\n", 2);
		return ;
	}
	if (error == 2)
	{
		ft_putstr_fd("Msh: syntax error near redirection\n", 2);
		return ;
	}
	if (error == 3)
	{
		ft_putstr_fd("Msh: syntax error near '|'\n", 2);
		return ;
	}
}
