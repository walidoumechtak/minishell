/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 13:46:19 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/24 14:36:43 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_minishell *ptr)
{
	fill_with(ptr->str, '|', '\t');
	ptr->splited_pipe = ft_split(ptr->str, '|');
	ptr->out_access = 0;
	ptr->o_file = NULL;
}
