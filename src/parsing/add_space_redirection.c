/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:20:56 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/31 17:59:36 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_inside_singl_q(int *j, int *i, char *iter, char *temp)
{
	temp[++(*j)] = iter[*i];
	(*i)++;
	while (iter[*i] && iter[*i] != '\'')
		temp[++(*j)] = iter[(*i)++];
	temp[++(*j)] = iter[(*i)];
}

static void	fill_inside_double_q(int *j, int *i, char *iter, char *temp)
{
	temp[++(*j)] = iter[*i];
	(*i)++;
	while (iter[*i] && iter[*i] != '\"')
		temp[++(*j)] = iter[(*i)++];
	temp[++(*j)] = iter[(*i)];
}

/**
 * (*i)i-- : because there is i++ in the parent code
 * // while (iter[*i] == '>' || iter[*i] == '<')
 * // {
 * // }
*/

static void	add_space(int *j, int *i, char *iter, char *temp)
{
	if (iter[*i] == '>')
	{
		temp[++(*j)] = ' ';
		while (iter[*i] == '>')
			temp[++(*j)] = iter[(*i)++];
	}
	if (iter[*i] == '<')
	{
		temp[++(*j)] = ' ';
		while (iter[*i] == '<')
			temp[++(*j)] = iter[(*i)++];
	}
	temp[++(*j)] = ' ';
	(*i)--;
}

static void	body_loop(int *j, int *i, char *iter, char *temp)
{
	if (iter[*i] == '\"')
		fill_inside_double_q(j, i, iter, temp);
	else if (iter[*i] == '\'')
		fill_inside_singl_q(j, i, iter, temp);
	else
	{
		if (iter[*i] != '>' && iter[*i] != '<')
			temp[++(*j)] = iter[*i];
		else
			add_space(j, i, iter, temp);
	}
}

int	add_space_redirection(char **str)
{
	char	*temp;
	char	*iter;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!str || !*str)
		return (0);
	size = (is_there_append(*str) + is_there_heredoc(*str)
			+ is_there_in_red(*str) + is_there_out_red(*str)) * 2;
	temp = malloc((ft_strlen(*str) + size + 1) * sizeof(char));
	if (!temp)
		return (-1);
	iter = *str;
	while (iter[i])
	{
		body_loop(&j, &i, iter, temp);
		i++;
	}
	temp[++j] = '\0';
	free(*str);
	*str = temp;
	return (0);
}
