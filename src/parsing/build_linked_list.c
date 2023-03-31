/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 11:05:03 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/31 15:34:53 by woumecht         ###   ########.fr       */
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
	// t_list	*temp;
	// t_list	*temp2;
	// int		i;
	// int		j;

	// i = 0;
	// j = 0;

	state = handle_quotes(ptr);
	if (state != 0)
		return (state);
	state = build_list_1(ptr);
	if (state != 0)
		return (state);
	if (ptr->max_here > 16)
	{
		ft_putstr_fd("maximum here-document count exceeded", 2);
		free_linked_lists(ptr, 0);
		exit (2);
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
	

	// temp = ptr->list_cmd;
	// while (temp)
	// {
	// 	i = 0;
	// 	j = 0;
	// 	while (((t_cmd *)temp->content)->cmd[i])
	// 		printf("cmd[] : %s\n", ((t_cmd *)temp->content)->cmd[i++]);
	// 	printf("in : %d\n", ((t_cmd *)temp->content)->fd_in);
	// 	printf("out : %d\n", ((t_cmd *)temp->content)->fd_out);
	// 	printf("---------------- end of pipe ------------------\n\n");
	// 	printf("---------  the new list of files opened -----------\n");
	// 	temp2 = ((t_cmd *)temp->content)->opened_files;
	// 	while (temp2)
	// 	{
	// 		printf("file : %s\n", ((t_open_file *)temp2->content)->file);
	// 		printf("fd : %d\n", ((t_open_file *)temp2->content)->fd);
	// 		printf("mode : %d\n", ((t_open_file *)temp2->content)->mode);
	// 		temp2 = temp2->next;
	// 	}
	// 	printf("-------- the end of new list ---------- \n\n");
	// 	temp = temp->next;
	// }


	return (0);
}
