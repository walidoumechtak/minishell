/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_there_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:20:10 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/02 16:05:42 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_there_heredoc(char *str)
{
    int i;
    int cpt;

    i = 0;
    cpt = 0;
    while (str[i])
    {
        if (str[i] == '<' && str[i + 1] && str[i + 1] == '<' && str[i + 2] != '<' && str[i - 1] != '<')
        {
            cpt++;   
            i += 2;
            continue;
        }
        i++;
    }
    return (cpt);
}