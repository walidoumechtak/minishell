/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_with.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:26:48 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/30 11:23:10 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	singl_case_qoutes(char *str, int *i, char old, char c)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		if (str[*i] == old)
			str[*i] = c;
		(*i)++;
	}
}

void	fill_with(char *str, char old, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\"' && str[i + 1] != '\0')
		{
			i++;
			while (str[i] && str[i] != '\"')
			{
				if (str[i] == old)
					str[i] = c;
				i++;
			}
		}
		else if (str[i] == '\'' && str[i + 1] != '\0')
			singl_case_qoutes(str, &i, old, c);
		i++;
	}
}
