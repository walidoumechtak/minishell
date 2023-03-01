/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_there_out_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:14:58 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/01 16:43:00 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_it(char *str)
{
    int i;
    int cpt;

    i = 0;
    cpt = 0;
    while (str[i])
    {
        if (str[i] == '>')
        {
            cpt++;   
            i++;
            continue;
        }
        i++;
    }
    return (cpt);
}

int is_there_out_redirection(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (str[i] == '\"')
        {
            i++;
            while (str[i] != '\"')
            {
                str[i] = '_';
                i++;
            }
            i++;
            continue ;
        }
        else if (str[i] == '\'')
        {
            i++;
            while (str[i] != '\'')
            {
                str[i] = '_';
                i++;
            }
        }
        i++;
    }
    return (check_it(str));
}