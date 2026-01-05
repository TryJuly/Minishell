/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:37:13 by strieste          #+#    #+#             */
/*   Updated: 2026/01/05 15:22:28 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	help_count_dollar_v2(char *str, int *quote, int *count, int *par);
static void	help_count_dollar_v1(char *str, int *quote, int *count);

int	count_dollars(char *str)
{
	int	i;
	int	par;
	int	count;
	int	quote;

	i = 0;
	count = 0;
	par = 0;
	quote = 0;
	while (str[i])
	{
		help_count_dollar_v1(&str[i], &quote, &count);
		if (str[i] == ' ' && !quote)
		{
			while (str[i] == ' ')
				i++;
			count++;
			continue ;
		}
		help_count_dollar_v2(&str[i], &quote, &count, &par);
		i++;
	}
	return (count);
}

static void	help_count_dollar_v1(char *str, int *quote, int *count)
{
	int	i;

	i = 0;
	if (str[i] == '\'' && !*quote)
		*quote += 1;
	else if (str[i] == '\'' && *quote)
	{
		*quote -= 1;
		*count += 1;
	}
	if (str[i] == '"' && !*quote)
		*quote += 1;
	else if (str[i] == '"' && *quote)
	{
		*quote -= 1;
		*count += 1;
	}
	return ;
}

static void	help_count_dollar_v2(char *str, int *quote, int *count, int *par)
{
	int	i;

	i = 0;
	if (str[i] == '(')
		*par = 1;
	if (str[i] == ')')
		*par = 0;
	if (str[i] == '$' && !*quote && *par == 0)
		*count += 1;
	return ;
}

char	*blank_space(char *str, int *i, int *j)
{
	char	*temp;

	*j = *i + 1;
	while (str[*j] == ' ')
		*j += 1;
	temp = ft_substr(str, *i, *j - *i);
	*i = *j - 1;
	return (temp);
}

char	*ft_unsplit(char **tab)
{
	char	*res;
	char	*temp;
	int		i;

	i = 0;
	res = NULL;
	temp = NULL;
	while (tab[i])
	{
		temp = ft_strjoin(res, tab[i]);
		if (!temp && !res)
			return (NULL);
		else if (!temp && res)
		{
			free(res);
			return (NULL);
		}
		if (res)
			free(res);
		res = temp;
		i++;
	}
	return (res);
}
