/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_v1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:28:54 by strieste          #+#    #+#             */
/*   Updated: 2026/01/23 12:52:48 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// static int	help_check_out(char c);

// int	is_out_check(char *str)
// {
// 	size_t	len;
// 	int		quote;
// 	int		res;

// 	len = 0;
// 	quote = 0;
// 	res = 0;
// 	while (str[len])
// 	{
// 		if ((str[len] == '\'' || str[len] == '"') && (!quote))
// 			quote = str[len++];
// 		if (str[len] == quote && (quote))
// 			quote = 0;
// 		if (!quote)
// 			res = help_check_out(str[len]);
// 		if (res == 1)
// 			return (g_exit_status = 2, 1);		// g_exit_status = 2
// 		if (str[len + 1] && str[len] == '|' && str[len + 1] == '|' && !quote)
// 			return (ft_putstr_fd("Msh: not taking || input\n", 2), 1);
// 		len++;
// 	}
// 	return (0);
// }

// static int	help_check_out(char c)
// {
// 	if ((unsigned char)c == ';')
// 		return (ft_putstr_fd("Msh: not taking `;'\n", 2), 1);
// 	if ((unsigned char)c == '&')
// 		return (ft_putstr_fd("Msh: not taking `&'\n", 2), 1);
// 	if ((unsigned char)c == '(')
// 		return (ft_putstr_fd("Msh: not taking `(' input\n", 2), 1);
// 	if ((unsigned char)c == ')')
// 		return (ft_putstr_fd("Msh: not taking `)' input\n", 2), 1);
// 	if ((unsigned char)c == '\\')
// 		return (ft_putstr_fd("Msh: not taking \\ input\n", 2), 1);
// 	if ((unsigned char)c == '*')
// 		return (ft_putstr_fd("Msh: not taking * input\n", 2), 1);
// 	return (0);
// }

// int	find_heredoc(char *str, t_data *data)
// {
// 	size_t	count;
// 	int		quote;

// 	count = 0;
// 	quote = 0;
// 	while (str[count])
// 	{
// 		if ((str[count] == '\'' || str[count] == '"') && (!quote))
// 			quote = str[count++];
// 		if (str[count] == quote && (quote))
// 			quote = 0;
// 		if (str[count] == '<' && str[count + 1] == '<' && !quote)
// 		{
// 			heredoc(&str[count + 2], data);
// 			data->heredoc = 1;
// 			count += 2;
// 		}
// 		count++;
// 	}
// 	return (0);
// }