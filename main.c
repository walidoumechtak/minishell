/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:48:56 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/03 15:56:37 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
    t_minishell *ptr;
    pid_t   pid;

    ptr = malloc(sizeof(t_minishell));
    while (1)
    {
            ptr->str = readline(RED"Minishell"NONE GREEN"-$ "NONE);
            
            pid = fork();
            if (pid == 0)
            {
                parsing(ptr);
            }
            add_history(ptr->str); // ==> add to cammand history
            wait(NULL);
            free(ptr->str);
            free(ptr->splited_space);
            free(ptr->splited_pipe);
    }
    free(ptr);
}