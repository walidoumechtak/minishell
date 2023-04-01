/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_with2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:03:19 by woumecht          #+#    #+#             */
/*   Updated: 2023/04/01 12:06:05 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_with2(char **str, char old, char c)
{
	char	*iter;
	int		i;

	iter = *str;
	i = 0;
	if (!str || !*str)
		return ;
	while (iter[i])
	{
		if (iter[i] == old)
		{
			iter[i] = c;
		}
		i++;
	}
}
