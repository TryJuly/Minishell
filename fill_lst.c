/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:58:23 by strieste          #+#    #+#             */
/*   Updated: 2025/12/11 14:57:47 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int		count_args(char **array, int len);
static void		add_redir_node(char *redir, char *file, t_cmd **current);
static void		add_args_node(char *args, t_cmd **current);
static int		is_redir(char *str);
void			add_back(t_cmd **cmd, t_cmd *new);
static t_cmd	*malloc_args(t_cmd **current, char **array, size_t len);
t_cmd			*lst_last(t_cmd *cmd);

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
		current = malloc_args(&(current), array, len);
		while (array[len] && array[len][0] != '|')
		{
			if (is_redir(array[len]))
			{
				add_redir_node(array[len], array[len + 1], &(current));
				len += 2;
			}
			else
				add_args_node(array[len++], &(current));
		}
		add_back(&(lst), current);
		if ((array[len]) && array[len][0] == '|' && array[len + 1])
			len++;
	}
	return (lst);
}

void	print_lst(t_cmd *lst)
{
	size_t	count;
	t_cmd	*tmp;

	count = 0;
	tmp = lst;
	while (lst->args[count])
	{
		printf("%sArgument %ld: %s%s\n", GREEN, count, lst->args[count], NC);
		count++;
	}
	printf("%sPrint file redir%s\n", YELLOW, NC);
	while (tmp->redir->next)
	{
		printf("%sFile : %s%s\n", GREEN, tmp->redir->file, NC);
		printf("%sFile : %d%s\n", GREEN, tmp->redir->type, NC);
		tmp->redir = tmp->redir->next;
	}
	
}

static void	add_redir_node(char *redir, char *file, t_cmd **current)
{
	t_redir	*new;
	// t_redir	*tmp;
	
	new = ft_calloc(1, sizeof(t_redir *));
	if (!new)
	{
		printf("%sError Malloc add_redir_node%s\n", RED, NC);
		return ;
	}
	new->next = 0;
	if (redir[0] == '<')
	{
		new->file = ft_strdup(file);
		new->type = R_IN;
	}
	else if (redir[0] == '>')
	{
		new->file = ft_strdup(file);
		new->type = R_OUT;
	}
	else if (redir[0] == '<' && redir[1] == '<')
	{
		new->file = ft_strdup(file);
		new->type = R_HEREDOC;
	}
	else if (redir[0] == '>' && redir[1] == '>')
	{
		new->file = ft_strdup(file);
		new->type = R_APPEND;
	}
	// tmp = (*current)->redir;
	if (!(*current)->redir)
	{
		(*current)->redir = new;
		return ;
	}
	while ((*current)->redir->next)
		(*current)->redir = (*current)->redir->next;
	(*current)->redir->next = new;
	return ;
}

void	add_args_node(char *args, t_cmd **current)
{
	size_t	count;

	count = 0;
	while ((*current)->args[count])
		count++;
	(*current)->args[count++] = ft_strdup(args);
	(*current)->args[count] = 0;
	return ;
}

static t_cmd	*malloc_args(t_cmd **current, char **array, size_t len)
{
	(*current) = ft_calloc(1, sizeof(t_cmd *));
	if (!(*current))
		return (printf("%sError malloc fill_lst 2%s\n", RED, NC), NULL);
	(*current)->args = malloc((count_args(array, len) + 1) * sizeof(char**));
	if (!(*current)->args)
		return (printf("%sError malloc fill_lst 3%s\n", RED, NC), NULL);
	(*current)->redir = NULL;
	(*current)->next = NULL;
	return (*current);
}

static int	is_redir(char *str)
{
	if (str[0] == '>' || str[0] == '<')
		return (1);
	if (str[0] == '>' && str[1] == '>')
		return (1);
	if (str[0] == '<' && str[1] == '<')
		return (1);
	return (0);
}

static int	count_args(char **array, int len)
{
	size_t	count;

	count = 0;
	while (array[len] && array[len][0] != '|')
	{
		if (array[len][0] == '<' || array[len][0] == '<'
			|| (array[len][0] == '>' && array[len][0] == '>')
			|| (array[len][0] == '<' && array[len][0] == '<'))
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

t_cmd	*lst_last(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

// void	fill_lst(char **array)
// {
// 	size_t	len;
// 	size_t	count;
// 	size_t	save;
// 	char	**cmd_array;

// 	len = 0;
// 	save = 0;
// 	while (array[len])
// 	{
// 		count = 0;
// 		if (array[len][0] == '|')
// 			len++;
// 		while (array[len] && array[len][0] != '|')
// 			len++;
// 		cmd_array = malloc((len + 1) * sizeof(char**));
// 		if (!cmd_array)
// 			return ;
// 		count = 0;
// 		if (array[save][0] == '|')
// 			save++;
// 		while (array[save] && array[save][0] != '|')
// 			cmd_array[count++] = array[save++];
// 		cmd_array[count] = 0;
// 		free(cmd_array);
// 	}
// }
