/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:48:56 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/10 21:52:19 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
    t_minishell *ptr;
    int state;

    (void)av;
    (void)ac;
    ptr = malloc(sizeof(t_minishell));
    build_env_list(ptr, env);
    while (1)
    {
            ptr->str = readline(RED"Minishell"NONE GREEN"-$ "NONE);
            state = parsing(ptr);
            if (state == 1)
            {
                ft_perror("Error : sysntax Error\n", state);
                continue ;
            }
            add_history(ptr->str); // ==> add to cammand history
            free(ptr->str);
    }
    free(ptr);
}