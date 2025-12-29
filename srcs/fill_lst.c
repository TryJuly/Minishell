/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:58:23 by strieste          #+#    #+#             */
/*   Updated: 2025/12/29 14:11:55 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		add_redir_node(char *redir, char *file, t_cmd *current);
static void		add_args_node(char *argument, t_cmd *current);
static int		get_redir_type(char *redir);
static char		*remove_quote(char *str);

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
	char	*t_str;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
	{
		ft_putstr_fd("Msh: Error Malloc add_redir_node\n", 2);
		return ;
	}
	new->type = get_redir_type(redir);
	new->file = ft_strdup(file);
	new->next = NULL;
	t_str = remove_quote(new->file);
	free(new->file);
	new->file = t_str;
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
	// char	*tmp;
	char	*tmp_quote;

	count = 0;
	// tmp = ft_strtrim(argument, "\"'");
	tmp_quote = remove_quote(argument);
	// free(tmp);
	if (!current->args[0])
	{
			current->args[0] = tmp_quote;
		current->args[1] = NULL;
	}
	else
	{
		while (current->args[count])
			count++;
		current->args[count++] = tmp_quote;
		current->args[count] = 0;
	}
	return ;
}

static char	*remove_quote(char *str)
{
	size_t	count;
	int		quote;
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
			if (str[count + 1] && str[count] == quote)
				count++;
		}
		else
			result[len++] = str[count++];
	}
	result[len] = '\0';
	return (result);
}

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

static int	get_redir_type(char *redir)
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
