/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:11:04 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/09 11:44:30 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char *error_syntax(t_minishell *ptr)
// {
    
// }

int    parsing(t_minishell *ptr)
{
    int state;
    
    state = init_struct(ptr);
    if (state != 0)
        return (state);
    state = build_linked_list(ptr);
    if (state != 0)
        return (state);
    return (0);
}
