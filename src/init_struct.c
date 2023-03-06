/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 13:46:19 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/05 12:37:24 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    build_env_list(t_minishell *ptr)
{
    t_env   *env_node;
    
    int i;

    i = 0;
    ptr->env_head = NULL;
    while (ptr->env[i])
    {
        env_node = malloc(sizeof(t_env));
        env_node->envStr = ptr->env[i];
        ft_lstadd_back(&ptr->env_head, ft_lstnew(env_node));
        i++;
    }
}

void    init_struct(t_minishell *ptr)
{
    ptr->splited_pipe = ft_split(ptr->str, '|');
    build_env_list(ptr);
}