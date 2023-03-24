/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:30:46 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/24 14:33:45 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_2(char *str, int *i)
{
	if (str[*i] && str[*i + 1] == '\0')
		return (0);
	while (str[*i])
	{
		if (str[*i] == '\"')
			while (str[++*i] && str[*i] != '\"')
				;
		if (str[*i] == '\'')
			while (str[++*i] && str[*i] != '\'')
				;
		if (str[*i] && str[*i] == '|')
		{
			while (str[++*i] == ' ')
				;
			if (str[*i] == '|')
				return (1);
		}
		(*i)++;
	}
	return (0);
}

int	check_pipe_syntax(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	else
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '|')
			return (1);
		if (check_pipe_2(str, &i) == 1)
			return (1);
		i = ft_strlen(str) - 1;
		while (str[i] == ' ')
			i--;
		if (str[i] == '|')
			return (1);
		return (0);
	}
}

int	check_semi_colum(char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i] != NULL)
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == '\"')
				while (arr[i][++j] && arr[i][j] != '\"')
					;
			if (arr[i][j] == '\'')
				while (arr[i][++j] && arr[i][j] != '\'')
					;
			if (arr[i][j] == ';')
				return (1);
			if (arr[i][j] != '\0')
				j++;
		}
		i++;
	}
	return (0);
}

int	check_backslach(char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == '\'')
				while (arr[i][++j] && arr[i][j] != '\'')
					;
			if (arr[i][j] == '\\')
				return (1);
			if (arr[i][j] != '\0')
				j++;
		}
		i++;
	}
	return (0);
}

int	check_quotes_close(char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == '\'')
				while (arr[i][++j] && arr[i][j] != '\'')
					;
			if (arr[i][j] == '\0')
				return (1);
			if (arr[i][j] == '\"')
				while (arr[i][++j] && arr[i][j] != '\"')
					;
			if (arr[i][j] == '\0')
				return (1);
			if (arr[i][j] != '\0')
				j++;
		}
		i++;
	}
	return (0);
}
