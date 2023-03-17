/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uncoted_expaind.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 08:57:37 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/14 16:25:08 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// split the value and join it again
int    ft_uncoted_exapaind(t_minishell *ptr, char **str)
{
    char **split_var;
    char *temp;
    char *temp2;
    char *res;
    int i;
    t_list  *exp;

    temp = *str;
    exp = ptr->env;
    res = NULL;
    split_var = NULL;
    i = 0;
    if (temp[0] && temp[1] == '\0')
        return 0;
    if (temp[0] == '$' && temp[1] == '?')
        return (0);
    while (exp && temp[1])
    {
        if (ft_strncmp(((t_env *)exp->content)->env_var, temp + 1, ft_strlen(temp + 1) + ft_strlen(((t_env *)exp->content)->env_var)) == 0)
        {
            split_var = ft_split(((t_env *)exp->content)->env_value, ' ');
            while (split_var[i])
            {
               temp2 = ft_strjoin(res, split_var[i]);
               free(res);
               res = temp2;
               if (split_var[i + 1] != NULL)
               {
                    temp2 = ft_strjoin(res, " ");
                    free(res);
                    res = temp2;  
               }
               i++;
            }
            free(*str);
            free_spilte(split_var);
            *str = res;
            return 0;
        }
        exp = exp->next;
    }
    free(*str);
    free_spilte(split_var);
    *str = ft_calloc(1,1);
    return (0);
}