/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:58:23 by strieste          #+#    #+#             */
/*   Updated: 2026/01/05 14:35:23 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		add_redir_node(char *redir, char *file, t_cmd *current);
static void		add_args_node(char *argument, t_cmd *current);
static char		*remove_quote(char *str, int quote);

t_cmd	*fill_lst(char **array)
{
	size_t	len;
	t_cmd	*lst;
	t_cmd	*current;

	len = 0;
	lst = NULL;
	current = NULL;
	while (array[len])
	{
		current = malloc_args(array, len);
		while (array[len] && array[len][0] != '|')
		{
			if (is_redir(array[len]))
			{
				add_redir_node(array[len], array[len + 1], current);
				len += 2;
			}
			else
				add_args_node(array[len++], current);
		}
		add_back_lst(&lst, current);
		if ((array[len]) && array[len][0] == '|' && array[len + 1])
			len++;
	}
	return (lst);
}

static void	add_redir_node(char *redir, char *file, t_cmd *current)
{
	t_redir	*new;
	t_redir	*tmp;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
	{
		ft_putstr_fd("Msh: Error Malloc add_redir_node\n", 2);
		return ;
	}
	new->type = get_redir_type(redir);
	new->file = remove_quote(file, 0);
	if (!new->file)
		return ;
	new->next = NULL;
	if (current->redir == NULL)
		current->redir = new;
	else
	{
		tmp = current->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	add_args_node(char *argument, t_cmd *current)
{
	size_t	count;
	char	*tmp;

	count = 0;
	tmp = remove_quote(argument, 0);
	if (!tmp)
		return ;
	if (!current->args[0])
	{
		current->args[0] = tmp;
		current->args[1] = NULL;
	}
	else
	{
		while (current->args[count])
			count++;
		current->args[count++] = tmp;
		current->args[count] = 0;
	}
	return ;
}

static char	*remove_quote(char *str, int quote)
{
	size_t	count;
	char	*result;
	int		len;

	count = 0;
	quote = 0;
	len = 0;
	result = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (str[count])
	{
		if (str[count] == '\'' || str[count] == '"')
		{
			quote = str[count++];
			while (str[count] && str[count] != quote)
				result[len++] = str[count++];
			if (str[count] && str[count] == quote)
				count++;
		}
		else
			result[len++] = str[count++];
	}
	result[len] = '\0';
	return (result);
}
