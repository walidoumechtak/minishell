/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambiguous.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 11:46:40 by woumecht          #+#    #+#             */
/*   Updated: 2023/04/01 14:57:28 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ambiguous(char *str)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_split(str, '\b');
	while (arr[i])
		i++;
	if (i >= 2)
		return (free_spilte(arr), 111);
	return (free_spilte(arr), 0);
}
