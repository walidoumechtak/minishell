/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_shift.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:52:08 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/29 16:48:48 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_shift(char **arr, int i)
{
	int	j;
	int	temp;
	int	sim_i;

	temp = 0;
	while (arr[temp])
		temp++;
	free(arr[i]);
	free(arr[i + 1]);
	arr[i] = NULL;
	arr[i + 1] = NULL;
	j = 0;
	sim_i = i;
	while (j < 2)
	{
		i = sim_i;
		while (i < temp)
		{
			arr[i] = arr[i + 1];
			i++;
		}
		j++;
	}
}
