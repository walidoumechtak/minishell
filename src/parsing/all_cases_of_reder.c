/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_cases_of_reder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:46:20 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/28 11:53:13 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	out_f(t_minishell *ptr, t_cmd_v1 *skin, int i)
{
	ptr->o_file = malloc(sizeof(t_open_file));
	open_file(ptr, skin->cmd, 2, i);
}

void	in_f(t_minishell *ptr, t_cmd_v1 *skin, int i)
{
	ptr->o_file = malloc(sizeof(t_open_file));
	open_file(ptr, skin->cmd, 1, i);
}

int	here_f(t_minishell *ptr, t_cmd_v1 *skin, int i, int l)
{
	ptr->o_file = malloc(sizeof(t_open_file));
	if (skin->expaind_here[l] == 1)
	{
		ptr->o_file->fd = 0;
		if (open_heredoc(ptr, skin->cmd, i, 0) == 9)
		{
			free(ptr->o_file);
			return (9);
		}
		l++;
	}
	else
	{
		ptr->o_file->fd = 0;
		if (open_heredoc(ptr, skin->cmd, i, 404) == 9)
			return (free(ptr->o_file), 9);
		l++;
	}
	return (0);
}

int	all_cases(t_minishell *ptr, t_open_redirection *o)
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
			return (9);
	}
	else if (ft_strncmp(o->skin->cmd[o->i], ">>", len) == 0
		&& o->skin->flags_red[o->k++] == 1)
	{
		ptr->o_file = malloc(sizeof(t_open_file));
		open_file(ptr, o->skin->cmd, 3, o->i);
	}
	else if (++(o->i))
		ptr->o_file = NULL;
	return (0);
}
