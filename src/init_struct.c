/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 13:46:19 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/09 11:46:42 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_end_ofstring(char *str)
{
    int i;

    i = ft_strlen(str) - 1;
    while (str[i] == ' ')
        i--;
    if (str[i] == '|')
        return (1);
    return (0);
}

int    init_struct(t_minishell *ptr)
{
    if (check_end_ofstring(ptr->str) == 1)
        return (1);
    fill_with(ptr->str, '|', '\t');
    ptr->splited_pipe = ft_split(ptr->str, '|');
    return (0);
}