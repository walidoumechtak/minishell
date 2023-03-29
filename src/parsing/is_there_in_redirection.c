/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_there_in_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:14:58 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/29 16:47:34 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_there_in_red(char *str)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] != '<' && (i == 0 || str[i - 1] != '>'))
		{
			cpt++;
			i++;
			continue ;
		}
		else
			i++;
	}
	return (cpt);
}
