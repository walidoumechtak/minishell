/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 11:14:13 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/26 16:01:09 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_open_redirection
{
	t_list		*old;
	t_list		*new;
	t_cmd		*new_c;
	t_cmd_v1	*skin;
	int			i;
	int			k;
	int			l;
	int			state;
}				t_open_redirection;

static void	out_f(t_minishell *ptr, t_cmd_v1 *skin, int i)
{
	ptr->o_file = malloc(sizeof(t_open_file));
	open_file(ptr, skin->cmd, 2, i);
}

static void	in_f(t_minishell *ptr, t_cmd_v1 *skin, int i)
{
	ptr->o_file = malloc(sizeof(t_open_file));
	open_file(ptr, skin->cmd, 1, i);
}

static int	here_f(t_minishell *ptr, t_cmd_v1 *skin, int i, int l)
{
	ptr->o_file = malloc(sizeof(t_open_file));
	if (skin->expaind_here[l] == 1)
	{
		ptr->o_file->fd = 0;
		if (open_heredoc(ptr, skin->cmd, i, 0) == 9)
			return (9);
		l++;
	}
	else
	{
		ptr->o_file->fd = 0;
		if (open_heredoc(ptr, skin->cmd, i, 404) == 9)
			return (9);
		l++;
	}
	return (0);
}

static int	all_cases(t_minishell *ptr, t_open_redirection *o)
{
	int	len;

	len = ft_strlen(o->skin->cmd[o->i]);
	if (ft_strncmp(o->skin->cmd[o->i], ">", len) == 0
		&& o->skin->flags_red[o->k++] == 1)
		out_f(ptr, o->skin, o->i);
	else if (ft_strncmp(o->skin->cmd[o->i], "<", len) == 0
			&& o->skin->flags_red[o->k++] == 1)
		in_f(ptr, o->skin, o->i);
	else if (ft_strncmp(o->skin->cmd[o->i], "<<", len) == 0
			&& o->skin->flags_red[o->k++] == 1)
	{
		if (here_f(ptr, o->skin, o->i, o->l) == 9)
			return (free(o), 9);
	}
	else if (ft_strncmp(o->skin->cmd[o->i], ">>", len) == 0
			&& o->skin->flags_red[o->k++] == 1)
	{
		ptr->o_file = malloc(sizeof(t_open_file));
		open_file(ptr, o->skin->cmd, 3, o->i);
	}
	else if (o->skin->cmd == NULL)
		return (1);
	else
	{
		o->i++;
		ptr->o_file = NULL;
	}
	return (0);
}

void	init_open_redirection(t_minishell *ptr, t_open_redirection *o, t_list **old_node,
		t_cmd **new_cmd)
{
	if (!o)
	{
		ft_putstr_fd("Failed to alloc memory", 2);
		free (o);
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
	t_open_redirection *o;

	o = malloc(sizeof(t_open_redirection));
	init_open_redirection(ptr, o, old_node, new_cmd);
	while (((t_cmd_v1 *)o->old->content)->cmd[o->i]
		&& o->skin->cmd[o->i][0] != '\0')
	{
		o->state = all_cases(ptr, o);
		if (o->state == 9)
			return (o->state);
		else if (o->state == 1)
			break ;
		if (ptr->o_file != NULL && o->skin->cmd != NULL)
		{
			o->new = ft_lstnew(ptr->o_file);
			if (!o->new)
			{
				free(o);
				free_linked_lists(ptr, 1);
				exit (404);
			}
			ft_lstadd_back(&o->new_c->opened_files, o->new);
		}
	}
	free(o);
	return (0);
}