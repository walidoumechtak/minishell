/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:15:59 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/29 12:32:00 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_rep(t_repare_cmd *rep, char **str)
{
	rep->iter = *str;
	if (!rep->iter)
		return (1);
	rep->result = NULL;
	rep->sub = NULL;
	rep->i = 0;
	return (0);
}

void	end_of_while(t_repare_cmd *rep)
{
	rep->temp = ft_strjoin(rep->result, rep->sub);
	free(rep->sub);
	free(rep->result);
	rep->result = rep->temp;
}

void	end_of_reaper(t_repare_cmd *rep, char **str)
{
	free(*str);
	*str = rep->result;
	free(rep);
}

void	failed_alloc_reaper(t_minishell *ptr)
{
	free_linked_lists(ptr, 0);
	ft_putendl_fd("Error: memory allocation", 2);
	exit(1);
}

void	reaper_cmd(t_minishell *ptr, char **str)
{
	t_repare_cmd	*rep;

	rep = malloc(sizeof(t_repare_cmd));
	if (!rep)
		failed_alloc_reaper(ptr);
	if (init_rep(rep, str) == 1)
		return ;
	while (rep->iter[rep->i])
	{
		if (rep->iter[rep->i] == '\"')
			part_double(ptr, rep);
		else if (rep->iter[rep->i] == '\'')
			part_single(ptr, rep);
		else
		{
			if (rep->iter[rep->i] == '$' && rep->iter[rep->i])
				part_dollar(ptr, rep);
			else
				part_string(ptr, rep);
		}
		if (rep->iter[rep->i] != '\0')
			rep->i++;
		end_of_while(rep);
	}
	end_of_reaper(rep, str);
}
