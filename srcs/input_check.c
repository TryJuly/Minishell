/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:12:13 by strieste          #+#    #+#             */
/*   Updated: 2025/12/26 12:31:41 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	redir_check(char *str);
static int	quote_check(char *str);

int	input_brute(char *str, t_data *data)
{
	size_t	count;
	int		valide;
	int		end;

	count = 0;
	valide = 0;
	end = ft_strlen(str);
	count = skip_space(&str[count]);
	if (str[count] == '|' && str[count + 1] == '|')
		return (ft_putstr_fd("Msh: syntax error `||'\n", 2), 1);
	if (str[count] == '|' || str[end - 1] == '|')
		return (ft_putstr_fd("Msh: syntax error `|'\n", 2), 1);
	if (quote_check(&str[count]))
		valide = 1;
	if (is_out_check(&str[count]))
		valide = 1;
	if (redir_check(&str[count]))
		valide = 1;
	if (find_heredoc(&str[count], data))
		valide = 1;
	if (valide == 1)
		return (1);
	return (0);
}

static int	redir_check(char *str)
{
	size_t	len;
	int		quote;

	len = 0;
	quote = 0;
	len += skip_space(str);
	while (str[len])
	{
		if ((str[len] == '\'' || str[len] == '"') && !quote)
			quote = str[len++];
		if ((str[len] == '\'' || str[len] == '"') && quote)
			quote = 0;
		if (str[len] && !quote)
		{
			if (str[len] == 62 && str[len + 1] == 62 && str[len + 2] == 62)
				return (ft_putstr_fd("Msh: parse error near `>'\n", 2), 1);
			if (str[len] == 62 && str[len + 1] == 60)
				return (ft_putstr_fd("Msh: parse error near `<'\n", 2), 1);
		}
		len++;
	}
	return (0);
}

static int	quote_check(char *str)
{
	size_t	count;
	int		quote;

	count = 0;
	quote = 0;
	while (str[count])
	{
		if ((str[count] == '"' || str[count] == '\'') && !quote)
			quote = str[count++];
		if (quote && str[count])
		{
			while (str[count] && str[count] != quote)
				count++;
			if (!str[count])
				return (ft_putstr_fd("Msh: Unclosed quote\n", 2), 1);
			if (str[count] && str[count] == quote)
				quote = 0;
		}
		count++;
	}
	return (0);
}
