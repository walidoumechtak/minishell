/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_list_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:24:01 by woumecht          #+#    #+#             */
/*   Updated: 2023/04/01 13:45:45 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * open_file
	- function that open in-file only and just set the mode for out file
 * with out open it 
 * the outfiles are opend in another step (function - open_out())
*/

void	open_file(t_minishell *ptr, char **arr, int mode, int i)
{
	if (mode == 1)
	{
		if (check_ambiguous(arr[i + 1]) != 0 
			|| (arr[i + 1][0] == '\t' && arr[i + 1][1] == '\0'))
			ptr->o_file->fd = -2;
		else if (ft_strncmp(arr[i + 1], "/dev/stdin", ft_strlen(arr[i + 1])
				+ ft_strlen("/dev/stdin")) == 0)
			ptr->o_file->fd = 0;
		else if (ft_strncmp(arr[i + 1], "/dev/stdout", ft_strlen(arr[i + 1])
				+ ft_strlen("/dev/stdout")) == 0)
			ptr->o_file->fd = 1;
		else if (ft_strncmp(arr[i + 1], "/dev/stderr", ft_strlen(arr[i + 1])
				+ ft_strlen("/dev/stderr")) == 0)
			ptr->o_file->fd = 2;
		else
			ptr->o_file->fd = open(arr[i + 1], O_RDONLY);
		ptr->o_file->mode = 1;
	}
	else if (mode == 2)
		ptr->o_file->mode = 2;
	else if (mode == 3)
		ptr->o_file->mode = 3;
	ptr->o_file->file = ft_strdup(arr[i + 1]);
	free_and_shift(arr, i);
}

/*
	modes :
	1 --> infile
	2 --> outfile
	3 --> append
	4 --> heredoc
*/

/**
* build_list_2 - building the final linked list that should be
* sned to execute part we loop throw a linked list of file and 
* their file descriptor and assigne to each node 
* hes **cmd and in_fd and out_fd
*/

void	failed_alloc_listv2(t_minishell *ptr)
{
	free_linked_lists(ptr, 1);
	ft_putendl_fd("Error: memory allocation", 2);
	exit(1);
}

int	build_list_2(t_minishell *ptr)
{
	t_list	*temp;
	t_list	*new;
	int		state;

	temp = ptr->list_v1;
	ptr->list_cmd = NULL;
	while (temp)
	{
		ptr->cmd = malloc(sizeof(t_cmd));
		if (!ptr->cmd)
			failed_alloc_listv2(ptr);
		ptr->cmd->fd_in = 0;
		ptr->cmd->fd_out = 1;
		state = open_rederiction(ptr, &temp, &ptr->cmd);
		if (state != 0)
			return (free(ptr->cmd), state);
		ptr->cmd->cmd = ((t_cmd_v1 *)temp->content)->cmd;
		new = ft_lstnew(ptr->cmd);
		if (!new)
			failed_alloc_listv2(ptr);
		ft_lstadd_back(&ptr->list_cmd, new);
		temp = temp->next;
	}
	return (0);
}
