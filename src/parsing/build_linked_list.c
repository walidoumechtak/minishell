/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 11:05:03 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/29 16:52:07 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*   Error infile -> 7
*   Error outfile and append -> 8
*   Error heredoc -> 9
*/

int	check_slach_symbole(t_minishell *ptr)
{
	t_list	*temp;
	DIR		*dir;

	temp = ptr->list_cmd;
	while (temp != NULL)
	{
		dir = opendir(((t_cmd *)temp->content)->cmd[0]);
		if (dir != NULL)
		{
			open_error(ptr, ((t_cmd *)temp->content)->cmd[0],
				": is a directory\n", 126);
			closedir(dir);
			return (126);
		}
		temp = temp->next;
	}
	return (0);
}

int	build_linked_list(t_minishell *ptr)
{
	int	state;

	state = handle_quotes(ptr);
	if (state != 0)
		return (state);
	state = build_list_1(ptr);
	if (state != 0)
		return (state);
	state = build_list_2(ptr);
	if (state != 0)
		return (state);
	state = fill_fd(ptr);
	if (state != 0)
		return (state);
	state = check_slach_symbole(ptr);
	if (state != 0)
		return (state);
	return (0);
}
