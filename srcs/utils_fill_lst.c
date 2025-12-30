/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fill_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 11:34:48 by strieste          #+#    #+#             */
/*   Updated: 2025/12/30 11:37:04 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_redir(char *str)
{
	if (ft_strlen(str) == 1)
	{
		if (str[0] == '>' || str[0] == '<')
			return (1);
	}
	else if (ft_strlen(str) == 2)
	{
		if (str[0] == '>' && str[1] == '>')
			return (1);
		if (str[0] == '<' && str[1] == '<')
			return (1);
	}
	return (0);
}

int	get_redir_type(char *redir)
{
	if (ft_strlen(redir) == 2 && redir[0] == '>' && redir[1] == '>')
		return (R_APPEND);
	if (ft_strlen(redir) == 2 && redir[0] == '<' && redir[1] == '<')
		return (R_HEREDOC);
	if (ft_strlen(redir) == 1 && redir[0] == '>')
		return (R_OUT);
	if (ft_strlen(redir) == 1 && redir[0] == '<')
		return (R_IN);
	return (-1);
}
