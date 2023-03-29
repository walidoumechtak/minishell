/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 11:14:13 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/29 10:16:03 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_open_redirection(t_minishell *ptr, t_open_redirection *o,
		t_list **old_node, t_cmd **new_cmd)
{
	if (!o)
	{
		ft_putstr_fd("Error: Failed to alloc memory\n", 2);
		free(o);
		free_linked_lists(ptr, 1);
		exit(404);
	}
	o->i = 0;
	o->new_c = *new_cmd;
	o->old = *old_node;
	o->skin = (t_cmd_v1 *)o->old->content;
	o->new_c->opened_files = NULL;
	o->k = 0;
	o->l = 0;
}

/**
 * open_redirection - function that called when we itirate the first linked list
 * that mean every node of linked_list_v1 we call open_redirection
*/

int	open_rederiction(t_minishell *ptr, t_list **old_node, t_cmd **new_cmd)
{
	t_open_redirection	*o;

	o = malloc(sizeof(t_open_redirection));
	init_open_redirection(ptr, o, old_node, new_cmd);
	while (((t_cmd_v1 *)o->old->content)->cmd[o->i]
		&& o->skin->cmd[o->i][0] != '\0')
	{
		o->state = all_cases(ptr, o);
		if (o->state == 9)
			return (free(o), 9);
		if (ptr->o_file != NULL && o->skin->cmd != NULL)
		{
			o->new = ft_lstnew(ptr->o_file);
			if (!o->new)
			{
				ft_putstr_fd("Failed to alloc memory\n", 2);
				free(o);
				free_linked_lists(ptr, 1);
				exit(404);
			}
			ft_lstadd_back(&o->new_c->opened_files, o->new);
		}
	}
	return (free(o), 0);
}
