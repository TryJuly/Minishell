/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:58:23 by strieste          #+#    #+#             */
/*   Updated: 2025/12/18 09:32:05 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int		count_args(char **array, int len);
static void		add_redir_node(char *redir, char *file, t_cmd *current);
static void		add_args_node(char *argument, t_cmd *current);
static int		is_redir(char *str);
void			add_back(t_cmd **cmd, t_cmd *new);
static t_cmd	*malloc_args(char **array, size_t len);
t_cmd			*lst_last(t_cmd *cmd);
static int		get_redir_type(char *redir);

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
		add_back(&lst, current);
		if ((array[len]) && array[len][0] == '|' && array[len + 1])
			len++;
	}
	return (lst);
}
/*		Function for print linked list		*/
void	print_lst(t_cmd *lst)
{
	size_t	count;
	size_t	len;
	t_redir	*tmp;

	len = 0;
	while (lst)
	{
		count = 0;
		while (lst->args[count])
		{
			printf("%sArgument %ld: %s%s\n", GREEN, count, lst->args[count], NC);
			count++;
		}
		printf("%sPrint file redir%s\n", YELLOW, NC);
		tmp = lst->redir;
		while (tmp)
		{
			printf("%sFile : :%s:%s\n", GREEN, tmp->file, NC);
			printf("%sFile type : %d%s\n", GREEN, tmp->type, NC);
			tmp = tmp->next;
		}
		lst = lst->next;
		len++;
	}
	printf("Numbers of node : %ld\n", len);
}

static int	count_args(char **array, int len)
{
	size_t	count;

	count = 0;
	while (array[len] && array[len][0] != '|')
	{
		if (is_redir(array[len]))
		{
			if (array[len + 1])
				len += 2;
			else
				return (-1);
		}
		else
		{
			len++;
			count++;
		}
	}
	return (count);
}

static void	add_redir_node(char *redir, char *file, t_cmd *current)
{
	t_redir	*new;
	t_redir	*tmp;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
	{
		printf("%sError Malloc add_redir_node%s\n", RED, NC);
		return ;
	}
	new->type = get_redir_type(redir);
	new->file = ft_strdup(file);
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

	count = 0;
	if (!current->args[0])
	{
		if (argument[0] == '"' || argument[0] == '\'')
			current->args[0] = ft_strtrim(argument, "\"'");
		else
			current->args[0] = ft_strdup(argument);
		current->args[1] = NULL;
	}
	else
	{
		while (current->args[count])
			count++;
		if (argument[0] == '"' || argument[0] == '\'')
			current->args[count++] = ft_strtrim(argument, "\"'");
		else
			current->args[count++] = ft_strdup(argument);
		current->args[count] = 0;
	}
	return ;
}

static int	is_redir(char *str)
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

void	add_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*tmp;

	if (!new)
		return ;
	if (!(*cmd))
	{
		(*cmd) = new;
		return ;
	}
	if (!(*cmd)->next)
	{
		(*cmd)->next = new;
		return ;
	}
	tmp = lst_last(*cmd);
	tmp->next = new;
	return ;
}

static t_cmd	*malloc_args(char **array, size_t len)
{
	t_cmd *current;

	current = ft_calloc(1, sizeof(t_cmd));
	if (!current)
		return (printf("%sError malloc fill_lst 2%s\n", RED, NC), NULL);
	current->args = ft_calloc(count_args(array, len) + 1, sizeof(char*));
	if (!current->args)
		return (printf("%sError malloc fill_lst 3%s\n", RED, NC), NULL);	// FREE STRUCT EXIT()
	current->redir = NULL;
	current->next = NULL;
	return (current);
}

t_cmd	*lst_last(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
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

int	lst_size(t_cmd *cmd)
{
	size_t	len;
	t_cmd	*tmp;

	if (!cmd)
		return (0);
	len = 0;
	tmp = cmd;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}
