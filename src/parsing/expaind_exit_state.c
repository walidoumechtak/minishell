/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expaind_exit_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:22:31 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/19 12:22:38 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void expaind_exit_state(t_minishell *ptr, char **str)
{
    char *res;
    char    *temp_s;
    char *temp;
    char    *sub;
    int i;
    int s;
    int e;

    temp_s = *str;
    temp = NULL;
    res = NULL;
    i = 0;
    if (!*str)
        return ;
    while (temp_s[i])
    {
        if (temp_s[i] == '$' && temp_s[i + 1] == '?')
        {
            sub = ft_itoa(ptr->exit_state);
            i++;
        }
        else
        {
            s = i;
            while (temp_s[i] && (temp_s[i] != '$' || temp_s[i + 1] != '?'))
                i++;
            e = i - s;
            sub = ft_substr(temp_s, s, e);
        }
        if (temp_s[i] != '\0' && temp_s[i] != '$')
            i++;
        temp = ft_strjoin(res, sub);
        free(sub);
        free (res);
        res = temp;
    }
    free(*str);
    *str = res;
}