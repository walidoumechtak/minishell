/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expaind_exit_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:22:31 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/26 23:06:11 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static  void    exp_it(t_minishell *ptr, char *temp_s, char **res, int *i)
{
    char *sub;
    char    *temp;
    int s;
    int e;
    
    temp = NULL;
    if (temp_s[*i] == '$' && temp_s[*i + 1] == '?')
    {
        sub = ft_itoa(ptr->exit_state);
        (*i)++;
    }
    else
    {
        s = *i;
        while (temp_s[*i] && (temp_s[*i] != '$' || temp_s[*i + 1] != '?'))
            (*i)++;
        e = *i - s;
        sub = ft_substr(temp_s, s, e);
    }
    if (temp_s[*i] != '\0' && temp_s[*i] != '$')
        (*i)++;
    temp = ft_strjoin(*res, sub);
    free(sub);
    free (*res);
    *res = temp;
}

void expaind_exit_state(t_minishell *ptr, char **str)
{
    char *res;
    char    *temp_s;
    int i;

    temp_s = *str;
    res = NULL;
    i = 0;
    if (!*str)
        return ;
    while (temp_s[i]) // ptr, temp_s, s, e
    {
        exp_it(ptr, temp_s, &res, &i);
    }
    free(*str);
    *str = res;
}
