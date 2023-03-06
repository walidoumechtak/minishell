/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_there_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:11:47 by woumecht          #+#    #+#             */
/*   Updated: 2023/02/26 16:46:21 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_there_pipe(t_minishell *ptr)
{
    int i;
    int cpt;

    i = 0;
    cpt = 0;
    while (ptr->str[i])
    {
        if (ptr->str[i] == '|')
            cpt++;
        i++;
    }
    return (cpt);
}