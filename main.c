/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:48:56 by woumecht          #+#    #+#             */
/*   Updated: 2023/02/26 10:14:14 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
    t_minishell *ptr;
    
    ptr = malloc(sizeof(t_minishell));
    while (1)
    {
        ptr->str = readline(RED"Minishell"NONE GREEN"-$ "NONE);
        add_history(ptr->str); // ==> add to cammand history
        minishell(ptr);
        printf("%s \n", ptr->str);
    }
    free(ptr->str);
}