/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_array_of_nullter.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:28:36 by woumecht          #+#    #+#             */
/*   Updated: 2023/04/05 11:28:49 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shift_it(char **arr, int i)
{
	int	temp;

	temp = 0;
	while (arr[temp])
		temp++;
	free(arr[i]);
	arr[i] = NULL;
	while (i < temp)
	{
		arr[i] = arr[i + 1];
		i++;
	}
}

void	shift_array_of_nullter(t_minishell *ptr)
{
	t_list	*temp;
	int		i;

	temp = ptr->list_cmd;
	while (temp)
	{
		i = 0;
		while (((t_cmd *)temp->content)->cmd[i])
		{
			if (((t_cmd *)temp->content)->cmd[i][0] == '\0')
				shift_it(((t_cmd *)temp->content)->cmd, i);
			if (((t_cmd *)temp->content)->cmd[i] != NULL
				&& ((t_cmd *)temp->content)->cmd[i][0] != '\0')
				i++;
		}
		temp = temp->next;
	}
}
