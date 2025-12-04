/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_v1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:58:59 by strieste          #+#    #+#             */
/*   Updated: 2025/12/04 15:30:04 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*help_function(char *cmd);
int			file_sort(t_data *data, char *file, char c, size_t count_data);

int	del_space_cmd_brut(t_data *data)
{
	size_t	len;
	char	*str;

	len = 0;
	while (data->cmd_brut[len])
	{
		str = ft_strtrim(data->cmd_brut[len], " ");
		if (!str)
			return (printf("%sError del_space_cmd_but%s\n", RED, NC), 1);
		free(data->cmd_brut[len]);
		data->cmd_brut[len] = str;
		len++;
	}
	return (0);
}

int	find_cmd_arg(t_data *data, char *cmd, size_t count_data)
{
	size_t	count;
	char	**array;
	char	*command;
	
	count = 0;
	array = ft_split(cmd, ' ');		// ! Data->cmd_brut change
	if (!array[count])
		return (printf("%s Error split_cmd%s\n", RED, NC), 1);
	while (array[count])
	{
		if ((array[count][0] == '<' || array[count][0] == '>') && array[count])	// if keycode before file store fd in struct
		{
		// 	if (file_sort(data, array[count + 1], array[count][0], count_data))
		// 		return (printf("%sError file_sort find_cmd_arg%s\n", RED, NC), 1);
			count += 2;
		}
		if (array[count][0] == '-' && array[count])
			data->arg[count_data] = ft_strdup(array[count]);	//		Need to check return strdup into data->arg
		else if (array[count])
		{
			command = find_path(array[count], data->path);		//		Need to check return find_path into command
			data->cmd[count_data] = command;
		}
		count++;
	}
	ft_free_array(array);
	return (0);
}

int	file_sort(t_data *data, char *file, char c, size_t count_data)
{
	if (c == '<')
	{
		if (infile_open(data, file, count_data))
			return (printf("%sError file_sort infile_open%s\n", RED, NC), 1);
	}
	else if (c == '>')
		if (outfile_open(data, file, count_data))
			return (printf("%sError file_sort outfile_open%s\n", RED, NC), 1);
	return (0);
}

/*		Create or Open/clear Outfile and store in data_struct	*/
int	outfile_open(t_data *data, char *outfile, size_t count_data)
{
	data->fd_outfile[count_data] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_outfile[count_data] == -1)
		return (printf("%sError open outfile%s/n", RED, NC), 1);
	return (0);
}

/*		Check infile, open and store in data_struct			*/
int	infile_open(t_data *data, char *infile, size_t	count_data)
{
	if (access(infile, F_OK))
		return (printf("%sError Access infile%s\n", RED, NC), 1);
	if (access(infile, R_OK))
		return (printf("%sError READ infile%s\n", RED, NC), 1);
	data->fd_infile[count_data] = open(infile, O_RDONLY);
	if (data->fd_infile[count_data] == -1)
		return (printf("%sError Open infile%s\n", RED, NC), 1);
	return (0);
}

int	clean_cmd_brut(t_data *data)
{
	size_t	len;
	char	*str;

	len = 0;
	while (data->cmd_brut[len])
	{
		str = ft_strtrim(data->cmd_brut[len], " ");
		if (!str)
			return (printf("Error clean_cmd_but\n"), 1);
		free(data->cmd_brut[len]);
		data->cmd_brut[len] = str;
		len++;
	}
	return (0);
}


char	*find_path(char *cmd, char **path)
{
	size_t	count;
	char	*command;
	
	if (cmd[0] == '/')
		return (help_function(cmd));
	else
	{
		command = NULL;
		count = 0;
		while (path[count])
		{
			command = ft_strcat(command, path[count]);
			command = ft_strcat(command, "/");
			command = ft_strcat(command, cmd);
			if (!access(command, F_OK) && !access(command, X_OK))
				return (command);
			free(command);
			command = NULL;
			count++;
		}
	}
	return (printf("Error acces PATH\n"), NULL);
}

static char	*help_function(char *cmd)
{	
	if (access(cmd, F_OK))
		return (printf("Chemin d'acces commande Invalide\n"), NULL);
	if (access(cmd, R_OK))
		return (printf("Erreur lecture chemin outifle\n"), NULL);
	if (access(cmd, X_OK))
		return (printf("Execution du chemin impossible\n"), NULL);
	if (!cmd)
		return (NULL);
	return (ft_strdup(cmd));
}
