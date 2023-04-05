/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 08:57:04 by woumecht          #+#    #+#             */
/*   Updated: 2023/04/05 07:27:50 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mode1(t_minishell *ptr, t_cmd *link1, t_open_file *link2)
{
	if (link2->fd == -2)
	{
		link1->fd_in = -1;
		ft_putendl_fd("ambiguous redirect", 2);
		ptr->exit_state = 1;
		return (7);
	}
	else if (link2->fd == -1)
	{
		link1->fd_in = -1;
		perror(link2->file);
		ptr->exit_state = 1;
		return (7);
	}
	else
	{
		if (link1->fd_in > 2)
			close(link1->fd_in);
		link1->fd_in = link2->fd;
	}
	return (0);
}

int	mode_here(t_minishell *ptr, t_cmd *link1, t_open_file *link2, int state)
{
	if (link2->mode == 4)
	{
		if (link1->fd_in > 2)
			close(link1->fd_in);
		if (link2->fd < 0)
		{
			link1->fd_in = -1;
			perror(link2->file);
			ptr->exit_state = 1;
			return (7);
		}
		link1->fd_in = link2->fd;
	}
	return (state);
}

int	other_mode(t_minishell *ptr, t_cmd *link1, t_open_file *link2)
{
	if ((link2->mode == 2 || link2->mode == 3))
	{
		if (link2->fd < 0)
		{
			if (link2->fd == -2)
				ft_putendl_fd("ambiguous redirect", 2);
			else
				perror(link2->file);
			link1->fd_out = -1;
			ptr->exit_state = 1;
			return (8);
		}
		else
		{
			if (link1->fd_out > 2)
				close(link1->fd_out);
			link1->fd_out = link2->fd;
		}
	}
	return (0);
}

int	fill_fd(t_minishell *ptr)
{
	t_list		*temp;
	t_list		*temp2;
	t_cmd		*link1;
	t_open_file	*link2;
	int			state;

	temp = ptr->list_cmd;
	while (temp)
	{
		state = 0;
		link1 = ((t_cmd *)temp->content);
		temp2 = ((t_cmd *)temp->content)->opened_files;
		while (temp2 && state != 7 && state != 8)
		{
			link2 = ((t_open_file *)temp2->content);
			if (link2->mode == 1 && mode1(ptr, link1, link2) == 7)
				state = 7;
			else if (other_mode(ptr, link1, link2) == 8)
				state = 8;
			state = mode_here(ptr, link1, link2, state);
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
	return (0);
}
