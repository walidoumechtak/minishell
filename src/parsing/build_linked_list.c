/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 11:05:03 by woumecht          #+#    #+#             */
/*   Updated: 2023/04/07 14:43:34 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*   Error infile -> 7
*   Error outfile and append -> 8
*   Error heredoc -> 9
*   if (((t_cmd *)temp->content)->cmd[i][0] != '\b')
*				fill_with2(&((t_cmd *)temp->content)->cmd[i++], '\b', ' ');
*	{ in case of (\bstring) --> will be " string" exemple : echo $non$ will be " $"
*	insted of "$"
*	}
*/

void	remove_del_from_res(t_minishell *ptr)
{
	t_list	*temp;
	int		i;

	temp = ptr->list_cmd;
	while (temp)
	{
		i = 0;
		while (((t_cmd *)temp->content)->cmd[i])
		{
			if (((t_cmd *)temp->content)->cmd[i][0] == '\b')
				((t_cmd *)temp->content)->cmd[i][0] = '\0';
			else if (((t_cmd *)temp->content)->cmd[i] != NULL
				&& ((t_cmd *)temp->content)->cmd[i][0] != '\b')
				fill_with2(&((t_cmd *)temp->content)->cmd[i], '\b', ' ');
			i++;
		}
		temp = temp->next;
	}
}

int	check_slach_symbole(t_minishell *ptr)
{
	t_list	*temp;
	DIR		*dir;

	temp = ptr->list_cmd;
	while (temp != NULL)
	{
		dir = opendir(((t_cmd *)temp->content)->cmd[0]);
		if (dir != NULL && ft_strchr(((t_cmd *)temp->content)->cmd[0], '/'))
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
	if (ptr->max_here > 16)
	{
		ft_putstr_fd("maximum here-document count exceeded\n", 2);
		free_linked_lists(ptr, 0);
		exit(2);
	}
	state = build_list_2(ptr);
	if (state != 0)
		return (state);
	state = fill_fd(ptr);
	if (state != 0)
		return (state);
	state = check_slach_symbole(ptr);
	if (state != 0)
		return (state);
	remove_del_from_res(ptr);
	return (0);
}
