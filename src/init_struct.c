/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 13:46:19 by woumecht          #+#    #+#             */
/*   Updated: 2023/02/26 14:46:02 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    init_struct(t_minishell *ptr)
{
    ptr->splited_pipe = ft_split(ptr->str, '|');
    while (ptr->splited_pipe)
        ptr->splited_redirection = ft_split();
}