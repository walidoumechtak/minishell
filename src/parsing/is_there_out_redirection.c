/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_there_out_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:14:58 by woumecht          #+#    #+#             */
/*   Updated: 2023/02/26 12:18:41 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_there_in_redirection(t_minishell *ptr)
{
    int i;
    int cpt;

    i = 0;
    cpt = 0;
    while (ptr->str[i])
    {
        if (ptr->str[i] == '>')
            cpt++;
        i++;
    }
    return (cpt);
}