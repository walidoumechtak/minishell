/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_there_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:20:10 by woumecht          #+#    #+#             */
/*   Updated: 2023/02/26 16:46:12 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_there_heredoc(t_minishell *ptr)
{
    int i;
    int cpt;

    i = 0;
    cpt = 0;
    while (ptr->str[i + 1])
    {
        if (ptr->str[i] == '<' && ptr->str[i+1] == '<')
            cpt++;
        i++;
    }
    return (cpt);
}