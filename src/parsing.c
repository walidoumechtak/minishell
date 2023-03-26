/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:11:04 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/26 14:38:02 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int    parsing(t_minishell *ptr)
{
    int state;
    
    if(check_quotes_close(ptr->splited_pipe) != 0)
        return (1);
    if (check_pipe_syntax(ptr->str) == 1)
		return (1);
    if (check_semi_colum(ptr->splited_pipe) != 0)
        return (1);
    if (check_backslach(ptr->splited_pipe) != 0)
        return (1);
    state = build_linked_list(ptr);
    if (state != 0)
        return (state);
    return (0);
}
